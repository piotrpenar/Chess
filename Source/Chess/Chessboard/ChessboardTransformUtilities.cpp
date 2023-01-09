// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessboardTransformUtilities.h"

#include "Chess/Enums/EColor.h"

void UChessboardTransformUtilities::Initialize(UChessData* ChessDataReference, AActor* ChessBoardOriginReference)
{
	ChessData = ChessDataReference;
	ChessBoardOrigin = ChessBoardOriginReference;
}

FTransform UChessboardTransformUtilities::GenerateChessPieceTransform(const FIntPoint Position, const EColor Color) const
{
	FTransform Transform = BoardToWorldTransform(Position);
	if (Color == EColor::Black)
	{
		FRotator Rotator = Transform.GetRotation().Rotator();
		Rotator.Yaw += 90;
		Transform.SetRotation(Rotator.Quaternion());
	}
	return Transform;
}

FTransform UChessboardTransformUtilities::GetChessBoardTransform() const
{
	return ChessBoardOrigin->GetActorTransform();
}

FTransform UChessboardTransformUtilities::BoardToWorldTransform(const FIntPoint Position) const
{
	FTransform Transform = GetChessBoardTransform();
	const float BoardDistance = ChessData->GetBoardCheckerSize();
	FVector PositionOffset = FVector(BoardDistance / 2 + Position.X * BoardDistance, BoardDistance / 2 + Position.Y * BoardDistance, ChessData->GetBoardOffset());
	PositionOffset = Transform.Rotator().RotateVector(PositionOffset);
	Transform.SetLocation(Transform.GetLocation() + PositionOffset);
	return Transform;
}
