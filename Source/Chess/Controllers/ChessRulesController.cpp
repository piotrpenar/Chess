


#include "ChessRulesController.h"

#include "Chess/ChessPieces/ChessPiece.h"


ECheckmateStatus UChessRulesController::GetBoardStatusForColor(UChessboard* Chessboard, EColor Color, IMovementVerifier* MovementVerifier)
{
	const EColor EnemyColor = Color == EColor::White ? EColor::Black : EColor::White;
	const TArray<UChessPiece*> AllyPieces = Chessboard->GetAllPiecesOfColor(Color);
	const TArray<UChessPiece*> EnemyPieces = Chessboard->GetAllPiecesOfColor(EnemyColor);
	const ECheckmateStatus CheckmateStatus = CalculateCheckmateStatus(EnemyPieces, AllyPieces, MovementVerifier);
	if (CheckmateStatus != ECheckmateStatus::None)
	{
		UE_LOG(LogTemp, Log, TEXT("Mate for Color %d - %d!"), Color, CheckmateStatus)
	}
	return CheckmateStatus;
}

bool UChessRulesController::IsKingInCheck(UChessboard* Chessboard, EColor Color)
{
	const EColor EnemyColor = Color == EColor::White ? EColor::Black : EColor::White;
	UChessPiece* AlliedKing = Chessboard->GetChessPiece(EFigure::King, Color);
	const TArray<UChessPiece*> EnemyPieces = Chessboard->GetAllPiecesOfColor(EnemyColor);
	const TArray<FEnemyMove> EnemiesAvailableMoves = GetEnemiesAvailableMoves(EnemyPieces);
	const TArray ThreateningEnemies = GetThreateningEnemies(EnemiesAvailableMoves, AlliedKing);
	return ThreateningEnemies.Num() > 0;
}


ECheckmateStatus UChessRulesController::CalculateCheckmateStatus(TArray<UChessPiece*> EnemyPieces, TArray<UChessPiece*> AllyPieces, IMovementVerifier* MovementVerifier)
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
		if (CanAllyEliminateCheck(EnemiesAvailableMoves, AllyPiece, MovementVerifier))
		{
			return CheckmateStatus;
		}
	}

	return ECheckmateStatus::Checkmate;
}

TArray<UChessRulesController::FEnemyMove> UChessRulesController::GetEnemiesAvailableMoves(TArray<UChessPiece*> EnemyPieces)
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

TArray<UChessPiece*> UChessRulesController::GetThreateningEnemies(TArray<FEnemyMove> EnemyMoves, UChessPiece* King)
{
	TArray<UChessPiece*> EndangeringFigures;
	for (FEnemyMove EnemyMove : EnemyMoves)
	{
		if (EnemyMove.Move.TargetObject == King)
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
		if (EnemyAvailableMoves.FindByPredicate([&KingMove](FEnemyMove& Move) { return KingMove.TargetPosition == Move.Move.TargetPosition; }) == nullptr)
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

bool UChessRulesController::CanAllyDestroyEnemy(const UChessPiece* ThreateningEnemy, UChessPiece* Ally, const FMove AllyMove, IMovementVerifier* MovementVerifier)
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

bool UChessRulesController::CanAllyEliminateCheck(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AllyPiece, IMovementVerifier* MovementVerifier)
{
	UChessPiece* ThreateningEnemy = EnemyAvailableMoves[0].Enemy;
	TArray<FMove> AllyAvailableMoves = AllyPiece->GetAvailableMoves();
	for (const FMove AllyMove : AllyAvailableMoves)
	{
		if (CanAllyDestroyEnemy(ThreateningEnemy, AllyPiece, AllyMove, MovementVerifier))
		{
			return true;
		}
		if (ThreateningEnemy->GetFigureType() != EFigure::Knight)
		{
			if (!CanAllyCoverAnyEnemyMove(EnemyAvailableMoves, AllyMove))
			{
				continue;
			}
			if (MovementVerifier->IsValidMove(AllyMove.TargetPosition, AllyPiece))
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
