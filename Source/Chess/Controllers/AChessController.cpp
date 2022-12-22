// Copyright Epic Games, Inc. All Rights Reserved.


#include "AChessController.h"

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
	Chessboard->GenerateEmptyBoard();
	ChessboardController = NewObject<UChessboardController>();
	ChessboardController->SetBoard(Chessboard);
	GenerateChessPieces(EColor::White);
	GenerateChessPieces(EColor::Black);
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
		Clone->SetColor(Color);
		Clone->SetPosition(Column, TargetRow);
		Clone->ChessData = ChessData;
		Clone->CreateActor(GetWorld(),this);
		Clone->SetActorTransform(GenerateChessPieceTransform(Column,TargetRow,Color));
		Clone->ChessGameState = this;
		Chessboard->SetPieceAtPosition(FVector2D(Column,TargetRow),Clone);
	}
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
	if(CurrentPlayer == EColor::White)
	{
		CurrentPlayer = EColor::Black;
	}
	else
	{
		CurrentPlayer = EColor::White;
	}
	ECheckmateStatus Status = RulesController->GetBoardStatusForColor(Chessboard,EColor::White,ChessboardController);
	UE_LOG(LogTemp, Log, TEXT("Check mate status is %D"),Status);
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
	//TODO: Fix this to move UChess aswell
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
		Actor->SetActorTransform(Chessboard->BoardToWorldTransform(Move.TargetPosition.X,Move.TargetPosition.Y));
		Actor->Position = Move.TargetPosition;
		Actor->Highlighter = this;
		CurrentHighlights.Add(Actor);
	}
}
EColor AChessController::GetCurrentPlayer()
{
	return CurrentPlayer;
}
