// Copyright Epic Games, Inc. All Rights Reserved.


#include "AChessController.h"

#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/F2DBoardArray.h"

void AChessController::BeginPlay()
{
	Super::BeginPlay();
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

UChessPiece* AChessController::GenerateChessPiece(const EFigureType Figure)
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

void AChessController::GenerateChessRow(TArray<EFigureType> Figures, const EColor Color, const int TargetRow)
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
	UE_LOG(LogTemp, Log, TEXT("Getting object from %s"),*FString(BoardPosition.ToString()))
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
	UE_LOG(LogTemp, Log, TEXT("Setting object at %s"),*FString(Vector2.ToString()))
	Board[Vector2.X].Set(Vector2.Y,ChessPiece);
}

void AChessController::CreateFigures(const EColor FigureColor)
{
	const bool bIsWhite = FigureColor == EColor::White;
	const int ManRow = bIsWhite ? 0 : 7;
	const int PawnRow = bIsWhite ? 1 : 6;
	TArray<EFigureType> MenTargetArray = Men;

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
