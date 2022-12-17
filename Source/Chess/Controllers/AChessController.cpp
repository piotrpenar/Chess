// Copyright Epic Games, Inc. All Rights Reserved.


#include "AChessController.h"

#include "Chess/ChessPieces/Logic/ChessBishop.h"
#include "Chess/ChessPieces/Logic/ChessKing.h"
#include "Chess/ChessPieces/Logic/ChessKnight.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"
#include "Chess/ChessPieces/Logic/ChessQueen.h"
#include "Chess/ChessPieces/Logic/ChessRook.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/F2DBoardArray.h"


void AChessController::InitializeChessPieces()
{
	FigureTypeMap = TMap<EFigureType,UChessPiece*>();
	UChessPawn* Pawn = NewObject<UChessPawn>(this);
	UChessRook* Rook =  NewObject<UChessRook>(this);
	UChessKnight* Knight =  NewObject<UChessKnight>(this);
	UChessBishop* Bishop =  NewObject<UChessBishop>(this);
	UChessQueen* Queen =  NewObject<UChessQueen>(this);
	UChessKing* King =  NewObject<UChessKing>(this);
	FigureTypeMap.Add(EFigureType::Pawn,Pawn);
	FigureTypeMap.Add(EFigureType::Rook,Rook);
	FigureTypeMap.Add(EFigureType::Knight,Knight);
	FigureTypeMap.Add(EFigureType::Bishop,Bishop);
	FigureTypeMap.Add(EFigureType::Queen,Queen);
	FigureTypeMap.Add(EFigureType::King,King);
}

void AChessController::BeginPlay()
{
	Super::BeginPlay();
	InitializeChessPieces();
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
	UChessPiece* Clone = NewObject<UChessPiece>();
	DuplicateObject(FigureTypeMap[Figure], Clone);
	return Clone;
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
		Clone->CreateActor(GetWorld(),Figures[i]);
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
