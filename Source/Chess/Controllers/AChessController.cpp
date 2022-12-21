// Copyright Epic Games, Inc. All Rights Reserved.


#include "AChessController.h"

#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigure.h"
#include "Chess/Utils/F2DBoardArray.h"

void AChessController::BeginPlay()
{
	Super::BeginPlay();
	RulesController = NewObject<UChessRulesController>();
	for (int i = 0; i < ChessData->BoardSize; i++)
	{
		F2DBoardArray Row = F2DBoardArray();
		for (int j = 0; j < ChessData->BoardSize; j++)
		{
			Row.Add(nullptr);
		}
		Board.Add(Row);
	}
	CreateChessPiece();
}

UChessPiece* AChessController::GenerateChessPiece(const EFigure Figure)
{
	return UChessPiecesFactory::GenerateChessPiece(Figure,this);
}

void AChessController::CreateChessPiece()
{
	CreateFigures(EColor::White);
	CreateFigures(EColor::Black);
}

FTransform AChessController::BoardToWorldTransform(const int X, const int Y) 
{
	FVector2D Position = FVector2D(X,Y);
	return BoardToWorldTransform(Position);
}

FTransform AChessController::GenerateChessPieceTransform(const int X,const  int Y,const  EColor Color)
{
	FTransform Transform = BoardToWorldTransform(X, Y);
	if(Color == EColor::Black)
	{
		FRotator Rotator = Transform.GetRotation().Rotator();
		Rotator.Yaw+=90;
		Transform.SetRotation(Rotator.Quaternion());
	}
	return Transform;
}

void AChessController::GenerateChessRow(TArray<EFigure> Figures, const EColor Color, const int TargetRow)
{
	for (int Column = 0; Column < ChessData->BoardSize; Column++)
	{
		UChessPiece* Clone = GenerateChessPiece(Figures[Column]);
		Clone->SetColor(Color);
		Clone->SetPosition(Column, TargetRow);
		Clone->ChessData = ChessData;
		Clone->BoardProvider = this;
		Clone->CreateActor(GetWorld(),this);
		Clone->SetActorTransform(GenerateChessPieceTransform(Column,TargetRow,Color));
		Clone->ChessGameState = this;
		Board[Column].Set(TargetRow,Clone);
	}
}

FTransform AChessController::BoardToWorldTransform(FVector2D Position)
{
	FTransform Transform= GetChessBoardTransform();
	const float BoardDistance = ChessData->BoardCheckerSize;
	Transform.SetLocation(Transform.GetLocation() + FVector(BoardDistance/2 + Position.X*BoardDistance,BoardDistance/2 + Position.Y*BoardDistance,ChessData->BoardOffset));
	return Transform;
}

UObject* AChessController::GetPieceAtPosition(FVector2D BoardPosition)
{
	//UE_LOG(LogTemp, Log, TEXT("Getting object from %s"),*FString(BoardPosition.ToString()))
	return Board[BoardPosition.X][BoardPosition.Y];
}

void AChessController::SetPieceAtPosition(const FVector2D Vector2, UObject* ChessPiece)
{
	UObject* CurrentObject = Board[Vector2.X][Vector2.Y];
	if(CurrentObject)
	{
		if(ChessPiece)
		{
			static_cast<UChessPiece*>(CurrentObject)->DestroyChessPiece();
		}
	}
	//UE_LOG(LogTemp, Log, TEXT("Setting object at %s"),*FString(Vector2.ToString()))
	Board[Vector2.X].Set(Vector2.Y,ChessPiece);
}


bool AChessController::IsValidMove(const FVector2D Position, UObject* ChessPiece)
{
	if(!ChessData->IsValidBoardPosition(Position))
	{
		return false;
	}
	UChessPiece* TargetPiece = static_cast<UChessPiece*>(ChessPiece);
	UChessPiece* SimulatedPiece = UChessPiecesFactory::CloneChessPiece(TargetPiece,this);
	TArray<F2DBoardArray> SimulatedBoard = TArray<F2DBoardArray>(Board);
	const FVector2D PreviousPosition = FVector2D(TargetPiece->GetBoardPosition());
	SimulatedBoard[Position.X].Set(Position.Y,SimulatedPiece);
	SimulatedPiece->SetPosition(Position.X,Position.Y);
	SimulatedBoard[PreviousPosition.X].Set(PreviousPosition.Y,nullptr);
	ECheckmateStatus Status = RulesController->GetBoardStatus(&SimulatedBoard,this,SimulatedPiece);
	return Status == ECheckmateStatus::None;
}

void AChessController::EndTurn(){
	if(CurrentPlayer == EColor::White)
	{
		CurrentPlayer = EColor::Black;
	}
	else
	{
		CurrentPlayer = EColor::White;
	}
	//ECheckMateStatus Status = RulesController->GetBoardStatus(&Board,this);
	//UE_LOG(LogTemp, Log, TEXT("Check mate status is %D"),Status);
}

TArray<UChessPiece*> AChessController::GetAllPiecesOfColor(const EColor Color)
{
	TArray<UChessPiece*> Pieces;
	for (F2DBoardArray Row : SourceBoard)
	{
		for (UObject* ChessPieceObject : Row.Array)
		{
			if (!ChessPieceObject)
			{
				continue;
			}
			UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
			if (ChessPiece->GetColor() == Color)
			{
				Pieces.Add(ChessPiece);
			}
		}
	}
	return Pieces;
}


UChessPiece* AChessController::GetChessPiece(const EFigure Figure,const EColor Color)
{
	for (F2DBoardArray Row : Board)
	{
		for (const UObject* ChessPieceObject : Row.Array)
		{
			if (!ChessPieceObject)
			{
				continue;
			}
			UChessPiece* ChessPiece = static_cast<UChessPiece*>(ChessPieceObject);
			if (ChessPiece->GetFigureType() == Figure && ChessPiece->GetColor() == Color)
			{
				return ChessPiece;
			}
		}
	}
	return nullptr;
}

void AChessController::CreateFigures(const EColor FigureColor)
{
	const bool bIsWhite = FigureColor == EColor::White;
	const int ManRow = bIsWhite ? 0 : 7;
	const int PawnRow = bIsWhite ? 1 : 6;
	TArray<EFigure> MenTargetArray = Men;

	if (!bIsWhite)
	{
		Algo::Reverse(MenTargetArray);
	}

	GenerateChessRow(MenTargetArray, FigureColor, ManRow);
	GenerateChessRow(Pawns, FigureColor, PawnRow);
};

void AChessController::SetSelectedFigure(AActor* Actor)
{
	AChessFigure* Figure = static_cast<AChessFigure*>(Actor);
	CurrentSelectedFigure = Figure;
}

void AChessController::HighlightSelected(AActor* Source)
{
	ClearHighlights();
	const ACheckerHighlight* CheckerHighlight = static_cast<ACheckerHighlight*>(Source);
	CurrentSelectedFigure->SourcePiece->MoveToPosition(CheckerHighlight->Position);
}

void AChessController::ClearHighlights()
{
	for (const auto Highlight : CurrentHighlights)
	{
		Highlight->Destroy();
	}
	CurrentHighlights.Empty();
}

void AChessController::CreateHighlights(TArray<FMove> Moves)
{
	UE_LOG(LogTemp, Log, TEXT("Generating highlights"))
	ClearHighlights();
	for (const auto Move : Moves)
	{
		ACheckerHighlight* Actor = GetWorld()->SpawnActor<ACheckerHighlight>(ChessData->GetCheckerHighlightActor());
		Actor->SetActorTransform(BoardToWorldTransform(Move.TargetPosition.X,Move.TargetPosition.Y));
		Actor->Position = Move.TargetPosition;
		Actor->Highlighter = this;
		CurrentHighlights.Add(Actor);
	}
}

FTransform AChessController::GetChessBoardTransform() const
{
	return ChessBoardOrigin->GetActorTransform();
}

EColor AChessController::GetCurrentPlayer()
{
	return CurrentPlayer;
}
