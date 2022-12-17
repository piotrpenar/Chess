// Copyright Epic Games, Inc. All Rights Reserved.


#include "AChessController.h"

#include "Chess/ChessPieces/UChessPawn.h"
#include "Chess/ChessPieces/UChessPiece.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/F2DBoardArray.h"


void AChessController::InitializeChessPieces()
{
	FigureTypeMap = TMap<EFigureType,UChessPiece*>();
	UChessPawn* Pawn = NewObject<UChessPawn>(this);
	UChessPawn* Rook =  NewObject<UChessPawn>(this);
	UChessPawn* Knight =  NewObject<UChessPawn>(this);
	UChessPawn* Bishop =  NewObject<UChessPawn>(this);
	UChessPawn* King =  NewObject<UChessPawn>(this);
	UChessPawn* Queen =  NewObject<UChessPawn>(this);
	FigureTypeMap.Add(EFigureType::Pawn,Pawn);
	FigureTypeMap.Add(EFigureType::Rook,Rook);
	FigureTypeMap.Add(EFigureType::Knight,Knight);
	FigureTypeMap.Add(EFigureType::Bishop,Bishop);
	FigureTypeMap.Add(EFigureType::King,King);
	FigureTypeMap.Add(EFigureType::Queen,Queen);
}

void AChessController::BeginPlay()
{
	Super::BeginPlay();
	InitializeChessPieces();
	for (int i = 0; i < BoardSize; i++)
	{
		TArray<UChessPiece*> Row = TArray<UChessPiece*>();
		for (int j = 0; j < BoardSize; j++)
		{
			Row.Add(nullptr);
		}
		Board.Add(F2DBoardArray());
		Board[i] = Row;
	}
	CreateChessPiece();
}

UChessPiece* AChessController::GenerateChessPiece(const EFigureType Figure)
{
	UChessPiece* Clone = NewObject<UChessPiece>();
	DuplicateObject(FigureTypeMap[Figure], Clone);
	return Clone;
}

void AChessController::CreateChessPiece()
{
	CreateFigures(EColor::White);
	CreateFigures(EColor::Black);
}

FTransform AChessController::GenerateChessPieceTransform(const int TargetRow,const  int TargetColumn,const  EColor Color) const
{
	FTransform Transform = ChessData->GetChessBoardTransform();
	Transform.SetLocation(Transform.GetLocation() + FVector(TargetRow,0,TargetColumn));
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
	for (int i = 0; i < BoardSize; i++)
	{
		UChessPiece* Clone = GenerateChessPiece(Figures[i]);
		Clone->SetColor(Color);
		Clone->SetPosition(TargetRow, i);
		Clone->CreateActor(ChessData,GetWorld());
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