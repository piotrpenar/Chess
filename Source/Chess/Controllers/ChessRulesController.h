#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Enums/ECheckmateStatus.h"
#include "ChessRulesController.generated.h"

USTRUCT()
struct FEnemyMove
{
	GENERATED_BODY()
		
	UPROPERTY()
	FMove Move;
	UPROPERTY()
	UChessPiece* Enemy;
};

UCLASS()
class CHESS_API UChessRulesController final : public UObject
{
	GENERATED_BODY()
	
	static TArray<FEnemyMove> GetEnemiesAvailableMoves(TArray<UChessPiece*> EnemyPieces);
	static TArray<UChessPiece*> GetThreateningEnemies(TArray<FEnemyMove> EnemyMoves, const UChessPiece* ChessPiece);
	static ECheckmateStatus CalculateCheckmateStatus(TArray<UChessPiece*> EnemyPieces, TArray<UChessPiece*> AllyPieces, IChessMovesProvider* MovesProvider);
	static UChessPiece* GetFigureFromArray(const TArray<UChessPiece*>& Array, const EFigure Figure);
	static bool IsKingAbleToEscape(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AlliedKing);
	static bool CanAllyCoverAnyEnemyMove(TArray<FEnemyMove> EnemyAvailableMoves, FMove AllyMove);
	static bool CanAllyDestroyEnemy(const UChessPiece* ThreateningEnemy, UChessPiece* Ally, const FMove AllyMove, IChessMovesProvider* MovementVerifier);
	static bool CanAllyEliminateCheck(TArray<FEnemyMove> EnemyAvailableMoves, UChessPiece* AllyPiece, IChessMovesProvider* MovesProvider);

public:
	static ECheckmateStatus GetCheckmateStatusForPlayer(UChessboard* Chessboard, EColor PlayerColor, IChessMovesProvider* MovesProvider);
	static bool IsKingInCheck(UChessboard* Chessboard, EColor Color);
};
