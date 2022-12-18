// Copyright Epic Games, Inc. All Rights Reserved.


#include "AChessController.h"

#include "Chess/ChessPieces/Logic/ChessBishop.h"
#include "Chess/ChessPieces/Logic/ChessKing.h"
#include "Chess/ChessPieces/Logic/ChessKnight.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"
#include "Chess/ChessPieces/Logic/ChessQueen.h"
#include "Chess/ChessPieces/Logic/ChessRook.h"
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

UChessPiece* AChessController::GetChessPiece(const FVector2D Position)
{
	return static_cast<UChessPiece*>(Board[static_cast<int>(Position.X)][static_cast<int>(Position.Y)]);
}

void AChessController::CreateChessPiece()
{
	CreateFigures(EColor::White);
	CreateFigures(EColor::Black);
}

FTransform AChessController::GenerateChessPieceTransform(const int TargetRow,const  int TargetColumn,const  EColor Color) const
{
	const float BoardDistance = ChessData->BoardCheckerSize;
	FTransform Transform = GetChessBoardTransform();
	Transform.SetLocation(Transform.GetLocation() + FVector(BoardDistance/2 + TargetRow*BoardDistance,BoardDistance/2 + TargetColumn*BoardDistance,0));
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
	for (int i = 0; i < ChessData->BoardSize; i++)
	{
		UChessPiece* Clone = GenerateChessPiece(Figures[i]);
		Clone->SetColor(Color);
		Clone->SetPosition(TargetRow, i);
		Clone->ChessData = ChessData;
		Clone->Board = Board;
		Clone->CreateActor(GetWorld());
		Clone->SetActorTransform(GenerateChessPieceTransform(TargetRow,i,Color));
		Board[TargetRow].Set(i,Clone);
	}
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

FTransform AChessController::GetChessBoardTransform() const
{
	return ChessBoardOrigin->GetActorTransform();
}
