#include "ChessRulesController.h"

ECheckmateStatus UChessRulesController::GetCheckmateStatusForPlayer(const UChessboardBase* Chessboard, const EColor PlayerColor, IMovementRulesProvider* MovementProvider)
{
	const EColor EnemyColor = PlayerColor == EColor::White ? EColor::Black : EColor::White;
	TArray<UChessPiece*> AllyPieces = Chessboard->GetAllPiecesOfColor(PlayerColor);
	TArray<UChessPiece*> EnemyPieces = Chessboard->GetAllPiecesOfColor(EnemyColor);
	const ECheckmateStatus CheckmateStatus = CalculateCheckmateStatus(EnemyPieces, AllyPieces, MovementProvider);
	return CheckmateStatus;
}

bool UChessRulesController::IsKingInCheck(const UChessboardBase* Chessboard, const EColor Color)
{
	const EColor EnemyColor = Color == EColor::White ? EColor::Black : EColor::White;
	const UChessPiece* AlliedKing = Chessboard->GetChessPieces(Color, EFigure::King)[0];
	TArray<UChessPiece*> EnemyPieces = Chessboard->GetAllPiecesOfColor(EnemyColor);
	TArray<FMove> EnemiesAvailableMoves = GetAvailableMovesForPieces(EnemyPieces);
	const TArray ThreateningEnemies = GetThreateningEnemies(EnemiesAvailableMoves, AlliedKing);
	return ThreateningEnemies.Num() > 0;
}

ECheckmateStatus UChessRulesController::CalculateCheckmateStatus(TArray<UChessPiece*>& EnemyPieces, TArray<UChessPiece*>& AllyPieces, IMovementRulesProvider* MovementProvider)
{
	UChessPiece* AlliedKing = GetFigureFromArray(AllyPieces, EFigure::King);
	ECheckmateStatus CheckmateStatus = ECheckmateStatus::None;
	const TArray<FMove> AlliedAvailableMoves = GetAvailableMovesForPieces(AllyPieces);
	TArray<FMove> EnemiesAvailableMoves = GetAvailableMovesForPieces(EnemyPieces);
	const TArray ThreateningEnemies = GetThreateningEnemies(EnemiesAvailableMoves, AlliedKing);
	const int ThreateningEnemiesCount = ThreateningEnemies.Num();

	if (ThreateningEnemiesCount > 0)
	{
		CheckmateStatus = ECheckmateStatus::Check;
	}

	const bool bIsKingAbleToEscape = IsKingAbleToEscape(EnemiesAvailableMoves, AlliedKing);

	if (!bIsKingAbleToEscape && ThreateningEnemiesCount > 1)
	{
		CheckmateStatus = ECheckmateStatus::Checkmate;
		return CheckmateStatus;
	}

	for (UChessPiece* AllyPiece : AllyPieces)
	{
		if (CanAllyEliminateCheck(EnemiesAvailableMoves, AllyPiece, MovementProvider))
		{
			return CheckmateStatus;
		}
	}

	if(ThreateningEnemiesCount == 0 && AlliedAvailableMoves.Num() ==0)
	{
		return ECheckmateStatus::Stalemate;
	}

	return ECheckmateStatus::Checkmate;
}

TArray<FMove> UChessRulesController::GetAvailableMovesForPieces(TArray<UChessPiece*>& Pieces)
{
	TArray<FMove> AllAvailableMoves;
	for (UChessPiece* Piece : Pieces)
	{
		AllAvailableMoves.Append(Piece->GetAvailableMoves());
	}
	return AllAvailableMoves;
}

TArray<UChessPiece*> UChessRulesController::GetThreateningEnemies(TArray<FMove>& AvailableMoves, const UChessPiece* ChessPiece)
{
	TArray<UChessPiece*> EndangeringFigures;
	for (const FMove Move : AvailableMoves)
	{
		if (Cast<UChessPiece>(Move.TargetObject) == ChessPiece)
		{
			EndangeringFigures.Add(Cast<UChessPiece>(Move.SourcePiece));
		}
	}
	return EndangeringFigures;
}

bool UChessRulesController::IsKingAbleToEscape(TArray<FMove>& EnemyAvailableMoves, UChessPiece* AlliedKing)
{
	const TArray<FMove> KingMoves = AlliedKing->GetAvailableMoves();
	for (FMove KingMove : KingMoves)
	{
		if (EnemyAvailableMoves.FindByPredicate([&KingMove](const FMove& Move) { return KingMove.TargetPosition == Move.TargetPosition; }) == nullptr)
		{
			return true;
		}
	}
	return false;
}

bool UChessRulesController::CanAllyCoverAnyMove(TArray<FMove>& EnemyAvailableMoves, FMove AllyMove)
{
	return EnemyAvailableMoves.FindByPredicate([&AllyMove](const FMove& Move) { return AllyMove.TargetPosition == Move.TargetPosition; }) == nullptr;
}

bool UChessRulesController::CanAllyDestroyEnemy(const UChessPiece* ThreateningEnemy, UChessPiece* Ally, const FMove AllyMove, IMovementRulesProvider* MovementVerifier)
{
	const UChessPiece* TargetPiece = Cast<UChessPiece>(AllyMove.TargetObject);
	if (TargetPiece == ThreateningEnemy)
	{
		if (MovementVerifier->IsValidMove(AllyMove.TargetPosition, Ally))
		{
			return true;
		}
	}
	return false;
}

bool UChessRulesController::CanAllyEliminateCheck(TArray<FMove>& EnemyAvailableMoves, UChessPiece* AllyPiece, IMovementRulesProvider* MovementProvider)
{
	UChessPiece* ThreateningEnemy = Cast<UChessPiece>(EnemyAvailableMoves[0].SourcePiece);
	TArray<FMove> AllyAvailableMoves = AllyPiece->GetAvailableMoves();
	for (const FMove AllyMove : AllyAvailableMoves)
	{
		if (CanAllyDestroyEnemy(ThreateningEnemy, AllyPiece, AllyMove, MovementProvider))
		{
			return true;
		}
		if (ThreateningEnemy->GetFigureType() != EFigure::Knight)
		{
			if (!CanAllyCoverAnyMove(EnemyAvailableMoves, AllyMove))
			{
				continue;
			}
			if (MovementProvider->IsValidMove(AllyMove.TargetPosition, AllyPiece))
			{
				return true;
			}
		}
	}
	return false;
}

UChessPiece* UChessRulesController::GetFigureFromArray(const TArray<UChessPiece*>& Array, const EFigure Figure)
{
	for (UChessPiece* ChessPiece : Array)
	{
		if (ChessPiece->GetFigureType() == Figure)
		{
			return ChessPiece;
		}
	}
	return nullptr;
}
