// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessboardMovementRulesBase.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"


void UChessboardMovementRulesBase::InitializeMovementRules(UChessData* ChessDataReference, UChessboardBase* ChessboardReference)
{
	ChessData = ChessDataReference;
	Chessboard = ChessboardReference;
}

bool UChessboardMovementRulesBase::IsValidMove(const FIntPoint Position, UObject* ChessPieceObject)
{
	return ChessData->IsValidBoardPosition(Position);
}

TArray<FMove> UChessboardMovementRulesBase::GetValidMovesFromPositions(const TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
{
	TArray<FMove> ValidMoves = TArray<FMove>();
	UChessPiece* ChessPiece = Cast<UChessPiece>(ChessPieceObject);
	TArray<FIntPoint> PossibleMoves = TArray(InputDirections);

	for (int i = 0; i < PossibleMoves.Num(); i++)
	{
		const FIntPoint PossibleMove = PossibleMoves[i];
		if (!IsValidMove(PossibleMove, ChessPiece))
		{
			continue;
		}
		UChessPiece* TargetObject = Chessboard->GetPieceAtPosition(PossibleMove);
		if (!TargetObject || TargetObject->GetColor() != ChessPiece->GetColor())
		{
			FMove Move = FMove(ChessPiece, PossibleMove, TargetObject);
			AdjustMoveType(&Move);
			ValidMoves.Add(Move);
		}
	}
	return ValidMoves;
}

TArray<FMove> UChessboardMovementRulesBase::GetValidMovesFromDirections(const TArray<FIntPoint> InputDirections, UObject* ChessPieceObject)
{
	TArray<FMove> AvailableMoves = TArray<FMove>();
	UChessPiece* ChessPiece = Cast<UChessPiece>(ChessPieceObject);
	TArray<FIntPoint> Directions = TArray(InputDirections);

	for (int i = 0; i < Directions.Num(); i++)
	{
		const FIntPoint Direction = Directions[i];
		FIntPoint NextPosition = FIntPoint(ChessPiece->GetBoardPosition());
		NextPosition += Direction;
		while (IsValidMove(NextPosition, ChessPiece))
		{
			if (UChessPiece* TargetObject = Chessboard->GetPieceAtPosition(NextPosition))
			{
				if (TargetObject->GetColor() != ChessPiece->GetColor())
				{
					AvailableMoves.Add(FMove(ChessPiece, NextPosition, TargetObject));
					break;
				}
				break;
			}
			else
			{
				AvailableMoves.Add(FMove(ChessPiece, NextPosition, TargetObject));
			}
			NextPosition += Direction;
		}
	}
	return AvailableMoves;
}

void UChessboardMovementRulesBase::AdjustMoveType(FMove* Move) const
{
	UChessPiece* SourcePiece = Cast<UChessPiece>(Move->SourcePiece);
	const bool bIsOnBoardEdge = Move->TargetPosition.Y == 0 || Move->TargetPosition.Y == ChessData->GetBoardSize() - 1;
	const bool bIsValidPawn = SourcePiece && SourcePiece->GetFigureType() == EFigure::Pawn;
	if (bIsValidPawn && bIsOnBoardEdge)
	{
		Move->MoveType = EMoveType::PawnPromotion;
	}
}

TArray<FMove> UChessboardMovementRulesBase::GetValidSpecialMoves(UObject* ChessPieceObject)
{
	UChessPiece* ChessPiece = Cast<UChessPiece>(ChessPieceObject);
	const EFigure TargetFigure = ChessPiece->GetFigureType();
	if (TargetFigure == EFigure::Pawn)
	{
		return GetPawnSpecialMoves(ChessPiece);
	}
	if (TargetFigure == EFigure::King)
	{
		return GetKingSpecialMoves(ChessPiece);
	}

	return {};
}


TArray<FMove> UChessboardMovementRulesBase::GetKingSpecialMoves(UChessPiece* KingPiece)
{
	TArray<FMove> SpecialMoves;
	const FIntPoint KingPos = KingPiece->GetBoardPosition();
	if (KingPiece->HasMoved())
	{
		return SpecialMoves;
	}
	TArray<UChessPiece*> Rooks = Chessboard->GetChessPieces(KingPiece->GetColor(), EFigure::Rook);
	for (UChessPiece* Rook : Rooks)
	{
		if (Rook->HasMoved() || Rook->GetBoardPosition().Y != KingPos.Y)
		{
			continue;
		}
		const int SignedDistance = Rook->GetBoardPosition().X - KingPiece->GetBoardPosition().X;
		const int Direction = FMath::Sign(SignedDistance);

		const FIntPoint FinalKingPosition = KingPos + FIntPoint(Direction * 2, 0);
		if (!IsValidMove(FinalKingPosition, KingPiece))
		{
			continue;
		}

		bool bCanCastle = true;
		for (int i = KingPos.X + Direction; i < FMath::Abs(SignedDistance) - 1; i += Direction)
		{
			const FIntPoint TargetPosition = FIntPoint(i, KingPos.Y);
			if (Chessboard->GetPieceAtPosition(TargetPosition))
			{
				bCanCastle = false;
				break;
			}
			if (!IsValidMove(TargetPosition, KingPiece))
			{
				bCanCastle = false;
				break;
			}
		}
		if (!bCanCastle)
		{
			continue;
		}

		SpecialMoves.Add(FMove(KingPiece, FinalKingPosition, Rook, EMoveType::Castling));
	}
	return SpecialMoves;
}

bool UChessboardMovementRulesBase::CanPawnDoubleMove(UChessPiece* ChessPiece, const FIntPoint PawnPos, const int Direction)
{
	if (ChessPiece->HasMoved())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Double Move"))
		return false;
	}
	TArray<FMove> SpecialMoves;
	bool bCanDoubleMove = true;
	FIntPoint TargetPosition = PawnPos;
	for (int i = 0; i < 2; i++)
	{
		TargetPosition += FIntPoint(0, Direction);
		if (!ChessData->IsValidBoardPosition(TargetPosition))
		{
			bCanDoubleMove = false;
			break;
		}
		const UChessPiece* OtherPiece = Chessboard->GetPieceAtPosition(TargetPosition);
		if (OtherPiece)
		{
			bCanDoubleMove = false;
			break;
		}
	}
	if (bCanDoubleMove && IsValidMove(TargetPosition, ChessPiece))
	{
		return true;
	}

	return false;
}

TArray<FMove> UChessboardMovementRulesBase::GetEnPassantMoves(UChessPiece* ChessPiece, const FIntPoint PawnPos, const int Direction)
{
	TArray<FMove> SpecialMoves;
	TArray EnPassantPositions =
	{
		FIntPoint(PawnPos.X - 1, PawnPos.Y),
		FIntPoint(PawnPos.X + 1, PawnPos.Y)
	};
	for (FIntPoint Position : EnPassantPositions)
	{
		if (!ChessData->IsValidBoardPosition(Position))
		{
			continue;
		}
		UChessPiece* OtherPiece = Chessboard->GetPieceAtPosition(Position);
		if (OtherPiece && OtherPiece->GetFigureType() == EFigure::Pawn && OtherPiece->GetColor() != ChessPiece->GetColor())
		{
			const UChessPawn* OtherPawn = Cast<UChessPawn>(OtherPiece);
			if (!OtherPawn->IsValidPassantTarget())
			{
				continue;
			}
			const FIntPoint PositionBehindTarget = Position + FIntPoint(0, Direction);
			if (IsValidMove(PositionBehindTarget, ChessPiece))
			{
				SpecialMoves.Add(FMove(ChessPiece, PositionBehindTarget, OtherPiece, EMoveType::EnPassant));
			}
		}
	}
	return SpecialMoves;
}

TArray<FMove> UChessboardMovementRulesBase::GetPawnSpecialMoves(UChessPiece* ChessPiece)
{
	TArray<FMove> SpecialMoves;
	const FIntPoint PawnPosition = ChessPiece->GetBoardPosition();
	const UChessPawn* Pawn = Cast<UChessPawn>(ChessPiece);
	const bool bHasMoved = Pawn->HasMoved();

	const int Direction = ChessPiece->GetColor() == EColor::White ? 1 : -1;

	if (bHasMoved)
	{
		return GetEnPassantMoves(ChessPiece, PawnPosition, Direction);
	}

	if (CanPawnDoubleMove(ChessPiece, PawnPosition, Direction))
	{
		return {FMove(ChessPiece, PawnPosition + FIntPoint(0, Direction * 2), nullptr, EMoveType::DoubleMove)};
	}

	return {};
}
