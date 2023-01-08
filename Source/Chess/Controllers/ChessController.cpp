// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChessController.h"

#include "ChessboardController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigure.h"
#include "Chess/Utils/F2DBoardArray.h"


void AChessController::BeginPlay()
{
	Super::BeginPlay();
	RulesController = NewObject<UChessRulesController>();
	Chessboard = NewObject<UChessboard>();
	Chessboard->Initialize(ChessData,ChessBoardOrigin);
	Chessboard->GenerateEmptyBoard();
	ChessboardController = NewObject<UChessboardController>();
	ChessboardController->Initialize(ChessData,Chessboard,this);
	GenerateChessPieces(EColor::White);
	GenerateChessPieces(EColor::Black);
	ChessboardController->CreateChessboardSimulation();
}

void AChessController::GenerateChessPieces(const EColor FigureColor)
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
}

void AChessController::GenerateChessRow(TArray<EFigure> Figures, const EColor Color, const int TargetRow)
{
	for (int Column = 0; Column < ChessData->GetBoardSize(); Column++)
	{
		UChessPiece* Clone = GenerateChessPiece(Figures[Column]);
		Clone->SetReferences(ChessData,ChessboardController,this);
		Clone->SetColor(Color);
		Clone->CreateActor(GetWorld(),this);
		Clone->SetPosition(Column, TargetRow);
		Clone->SetActorTransform(GenerateChessPieceTransform(Column,TargetRow,Color));
		Chessboard->SetPieceAtPosition(FIntPoint(Column,TargetRow),Clone);
	}
}

void AChessController::BroadcastTurnEnded(EColor Color)
{
	TurnEndedEvent.Broadcast(Color);
}

UChessPiece* AChessController::GenerateChessPiece(const EFigure Figure)
{
	return UChessPiecesFactory::GenerateChessPiece(Figure,this);
}

FTransform AChessController::GenerateChessPieceTransform(const int X,const  int Y,const  EColor Color)
{
	FTransform Transform = Chessboard->BoardToWorldTransform(X, Y);
	if(Color == EColor::Black)
	{
		FRotator Rotator = Transform.GetRotation().Rotator();
		Rotator.Yaw+=90;
		Transform.SetRotation(Rotator.Quaternion());
	}
	return Transform;
}


void AChessController::EndTurn(){
	EColor EnemyPlayer = CurrentPlayer == EColor::Black ? EColor::White : EColor::Black;
	if(CurrentPlayer == EColor::White)
	{
		CurrentPlayer = EColor::Black;
	}
	else
	{
		CurrentPlayer = EColor::White;
	}
	ECheckmateStatus Status = RulesController->GetBoardStatusForColor(Chessboard,EnemyPlayer,ChessboardController);
	FString Value= UEnum::GetValueAsString(Status);
	UE_LOG(LogTemp, Log, TEXT("Check mate status is %s"),*FString(Value));
}

void AChessController::SetSelectedFigure(AActor* Actor)
{
	AChessFigure* Figure = static_cast<AChessFigure*>(Actor);
	CurrentSelectedFigure = Figure;
}

void AChessController::HighlightSelected(AActor* Source)
{
	ClearHighlights();
	const ACheckerHighlight* CheckerHighlight = static_cast<ACheckerHighlight*>(Source);
	FIntPoint BoardPosition = CheckerHighlight->SourceFigure->GetBoardPosition();
	FIntPoint TargetPosition = CheckerHighlight->Position;
	UChessPiece* ChessPiece = ChessboardController->GetOtherPieceAtPosition(BoardPosition);
	ChessboardController->MoveChessPieceToPosition(ChessPiece,TargetPosition);
}

void AChessController::ClearHighlights()
{
	for (const auto Highlight : CurrentHighlights)
	{
		Highlight->Destroy();
	}
	CurrentHighlights.Empty();
}

AChessController::FTurnEnded& AChessController::OnTurnEnded()
{
	return TurnEndedEvent;
}

void AChessController::CreateHighlights(TArray<FMove> Moves)
{
	UE_LOG(LogTemp, Log, TEXT("Generating highlights"))
	ClearHighlights();
	for (const auto Move : Moves)
	{
		ACheckerHighlight* Actor = GetWorld()->SpawnActor<ACheckerHighlight>(ChessData->GetCheckerHighlightActor());
		Actor->SetActorTransform(Chessboard->BoardToWorldTransform(Move.TargetPosition.X,Move.TargetPosition.Y));
		Actor->Position = Move.TargetPosition;
		Actor->Highlighter = this;
		Actor->SourceFigure = CurrentSelectedFigure;
		Actor->Move = Move;
		CurrentHighlights.Add(Actor);
	}
}
EColor AChessController::GetCurrentPlayer()
{
	return CurrentPlayer;
}
