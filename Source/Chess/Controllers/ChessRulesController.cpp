#include "ChessRulesController.h"

ECheckmateStatus UChessRulesController::GetCheckmateStatusForPlayer(const UChessboardBase* Chessboard, const EColor PlayerColor, IMovementRulesProvider* MovementProvider)
{
	const EColor EnemyColor = PlayerColor == EColor::White ? EColor::Black : EColor::White;
	const TArray<UChessPiece*> AllyPieces = Chessboard->GetAllPiecesOfColor(PlayerColor);
	const TArray<UChessPiece*> EnemyPieces = Chessboard->GetAllPiecesOfColor(EnemyColor);
	const ECheckmateStatus CheckmateStatus = CalculateCheckmateStatus(EnemyPieces, AllyPieces, MovementProvider);
	if (CheckmateStatus != ECheckmateStatus::None)
	{
		UE_LOG(LogTemp, Log, TEXT("Mate for Color %d - %d!"), PlayerColor, CheckmateStatus)
	}
	return CheckmateStatus;
}

bool UChessRulesController::IsKingInCheck(const UChessboardBase* Chessboard, const EColor Color)
{
	const EColor EnemyColor = Color == EColor::White ? EColor::Black : EColor::White;
	const UChessPiece* AlliedKing = Chessboard->GetChessPieces( Color,EFigure::King)[0];
	const TArray<UChessPiece*> EnemyPieces = Chessboard->GetAllPiecesOfColor(EnemyColor);
	const TArray<FEnemyMove> EnemiesAvailableMoves = GetEnemiesAvailableMoves(EnemyPieces);
	const TArray ThreateningEnemies = GetThreateningEnemies(EnemiesAvailableMoves, AlliedKing);
	return ThreateningEnemies.Num() > 0;
}

ECheckmateStatus UChessRulesController::CalculateCheckmateStatus(const TArray<UChessPiece*> EnemyPieces, TArray<UChessPiece*> AllyPieces, IMovementRulesProvider* MovementProvider)
{
	UChessPiece* AlliedKing = GetFigureFromArray(AllyPieces, EFigure::King);
	ECheckmateStatus CheckmateStatus = ECheckmateStatus::None;
	const TArray<FEnemyMove> EnemiesAvailableMoves = GetEnemiesAvailableMoves(EnemyPieces);
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

	return ECheckmateStatus::Checkmate;
}

TArray<FEnemyMove> UChessRulesController::GetEnemiesAvailableMoves(TArray<UChessPiece*> EnemyPieces)
{
	TArray<FEnemyMove> AllEnemyAvailableMoves = TArray<FEnemyMove>();
	for (UChessPiece* EnemyPiece : EnemyPieces)
	{
		TArray<FMove> EnemyAvailableMoves = EnemyPiece->GetAvailableMoves();
		for (const FMove Move : EnemyAvailableMoves)
		{
			AllEnemyAvailableMoves.Add({Move, EnemyPiece});
		}
	}
	return AllEnemyAvailableMoves;
}

TArray<UChessPiece*> UChessRulesController::GetThreateningEnemies(TArray<FEnemyMove> EnemyMoves, const UChessPiece* ChessPiece)
{
	TArray<UChessPiece*> EndangeringFigures;
	for (FEnemyMove EnemyMove : EnemyMoves)
	{
		if (EnemyMove.Move.TargetObject == ChessPiece)
		{
			EndangeringFigures.Add(EnemyMove.Enemy);
		}
	}
	return EndangeringFigures;
}

bool UChessRulesController::IsKingAbleToEscape(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AlliedKing)
{
	const TArray<FMove> KingMoves = AlliedKing->GetAvailableMoves();
	for (FMove KingMove : KingMoves)
	{
		if (EnemyAvailableMoves.FindByPredicate([&KingMove](const FEnemyMove& Move) { return KingMove.TargetPosition == Move.Move.TargetPosition; }) == nullptr)
		{
			return true;
		}
	}
	return false;
}

bool UChessRulesController::CanAllyCoverAnyEnemyMove(TArray<FEnemyMove> EnemyAvailableMoves, FMove AllyMove)
{
	return EnemyAvailableMoves.FindByPredicate([&AllyMove](const FEnemyMove& Move) { return AllyMove.TargetPosition == Move.Move.TargetPosition; }) == nullptr;
}

bool UChessRulesController::CanAllyDestroyEnemy(const UChessPiece* ThreateningEnemy, UChessPiece* Ally, const FMove AllyMove, IMovementRulesProvider* MovementVerifier)
{
	const UChessPiece* TargetPiece = static_cast<UChessPiece*>(AllyMove.TargetObject);
	if (TargetPiece == ThreateningEnemy)
	{
		if (MovementVerifier->IsValidMove(AllyMove.TargetPosition, Ally))
		{
			return true;
		}
	}
	return false;
}

bool UChessRulesController::CanAllyEliminateCheck(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AllyPiece, IMovementRulesProvider* MovementProvider)
{
	UChessPiece* ThreateningEnemy = EnemyAvailableMoves[0].Enemy;
	TArray<FMove> AllyAvailableMoves = AllyPiece->GetAvailableMoves();
	for (const FMove AllyMove : AllyAvailableMoves)
	{
		if (CanAllyDestroyEnemy(ThreateningEnemy, AllyPiece, AllyMove, MovementProvider))
		{
			return true;
		}
		if (ThreateningEnemy->GetFigureType() != EFigure::Knight)
		{
			if (!CanAllyCoverAnyEnemyMove(EnemyAvailableMoves, AllyMove))
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
