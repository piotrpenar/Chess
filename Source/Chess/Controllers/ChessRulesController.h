#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Enums/ECheckmateStatus.h"
#include "ChessRulesController.generated.h"

UCLASS()
class CHESS_API UChessRulesController final : public UObject
{
	GENERATED_BODY()

	struct FEnemyMove
	{
		FMove Move;
		UChessPiece* Enemy;
	};

	static TArray<FEnemyMove> GetEnemiesAvailableMoves(TArray<UChessPiece*> EnemyPieces);
	static TArray<UChessPiece*> GetThreateningEnemies(TArray<FEnemyMove> EnemyMoves, UChessPiece* King);
	static ECheckmateStatus CalculateCheckmateStatus(TArray<UChessPiece*> EnemyPieces, TArray<UChessPiece*> AllyPieces, IMovementVerifier* MovementVerifier);
	static UChessPiece* GetFigureFromArray(const TArray<UChessPiece*>& Array, const EFigure Figure);
	static bool IsKingAbleToEscape(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AlliedKing);
	static bool CanAllyCoverAnyEnemyMove(TArray<FEnemyMove> EnemyAvailableMoves, FMove AllyMove);
	static bool CanAllyDestroyEnemy(const UChessPiece* ThreateningEnemy, UChessPiece* Ally, const FMove AllyMove, IMovementVerifier* MovementVerifier);
	static bool CanAllyEliminateCheck(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AllyPiece, IMovementVerifier* MovementVerifier);

public:
	static ECheckmateStatus GetBoardStatusForColor(UChessboard* Chessboard, EColor Color, IMovementVerifier* MovementVerifier);
	static bool IsKingInCheck(UChessboard* Chessboard, EColor Color);
};
