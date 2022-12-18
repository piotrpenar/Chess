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

FTransform AChessController::BoardToWorldTransform(const int X, const int Y) const
{
	FTransform Transform= GetChessBoardTransform();
	const float BoardDistance = ChessData->BoardCheckerSize;
	Transform.SetLocation(Transform.GetLocation() + FVector(BoardDistance/2 + X*BoardDistance,BoardDistance/2 + Y*BoardDistance,0));
	return Transform;
}

FTransform AChessController::GenerateChessPieceTransform(const int X,const  int Y,const  EColor Color) const
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

UObject* AChessController::GetPieceAtPosition(FVector2D BoardPosition)
{
	UE_LOG(LogTemp, Log, TEXT("Getting object from %s"),*FString(BoardPosition.ToString()))
	return Board[BoardPosition.X][BoardPosition.Y];
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

void AChessController::CreateHighlight(TArray<FMove> Moves)
{
	for (const auto Move : Moves)
	{
		ACheckerHighlight* Actor = GetWorld()->SpawnActor<ACheckerHighlight>(ChessData->GetCheckerHighlightActor());
		Actor->SetActorTransform(BoardToWorldTransform(Move.TargetPosition.X,Move.TargetPosition.Y));
		CurrentHighlights.Add(Actor);
	}
}

FTransform AChessController::GetChessBoardTransform() const
{
	return ChessBoardOrigin->GetActorTransform();
}
