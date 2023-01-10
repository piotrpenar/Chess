#include "ChessSceneUtilities.h"
#include "Chess/Enums/EColor.h"

void UChessSceneUtilities::Initialize(UChessData* ChessDataReference, AActor* ChessBoardOriginReference)
{
	ChessData = ChessDataReference;
	ChessBoardOrigin = ChessBoardOriginReference;
}

FTransform UChessSceneUtilities::GenerateChessPieceTransform(const FIntPoint Position, const EColor Color) const
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

FTransform UChessSceneUtilities::GetChessBoardTransform() const
{
	return ChessBoardOrigin->GetActorTransform();
}

FTransform UChessSceneUtilities::BoardToWorldTransform(const FIntPoint Position) const
{
	FTransform Transform = GetChessBoardTransform();
	const float BoardDistance = ChessData->GetBoardCheckerSize();
	FVector PositionOffset = FVector(BoardDistance / 2 + Position.X * BoardDistance, BoardDistance / 2 + Position.Y * BoardDistance, ChessData->GetBoardOffset());
	PositionOffset = Transform.Rotator().RotateVector(PositionOffset);
	Transform.SetLocation(Transform.GetLocation() + PositionOffset);
	return Transform;
}

UWorld* UChessSceneUtilities::GetBoardWorld() const
{
	return ChessBoardOrigin->GetWorld();
}
