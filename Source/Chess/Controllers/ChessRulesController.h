#pragma once

#include "CoreMinimal.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Enums/ECheckmateStatus.h"
#include "Chess/Interfaces/MovementRulesProvider.h"
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

	static TArray<FMove> GetAvailableMovesForPieces(TArray<UChessPiece*>& Pieces);
	static TArray<UChessPiece*> GetThreateningEnemies(TArray<FMove>& AvailableMoves, const UChessPiece* ChessPiece);
	static ECheckmateStatus CalculateCheckmateStatus(TArray<UChessPiece*>& EnemyPieces, TArray<UChessPiece*>& AllyPieces, IMovementRulesProvider* MovementProvider);
	static UChessPiece* GetFigureFromArray(const TArray<UChessPiece*>& Array, const EFigure Figure);
	static bool IsKingAbleToEscape(TArray<FMove>& EnemyAvailableMoves, UChessPiece* AlliedKing);
	static bool CanAllyCoverAnyMove(TArray<FMove>& EnemyAvailableMoves, FMove AllyMove);
	static bool CanAllyDestroyEnemy(const UChessPiece* ThreateningEnemy, UChessPiece* Ally, const FMove AllyMove, IMovementRulesProvider* MovementVerifier);
	static bool CanAllyEliminateCheck(TArray<FMove>& EnemyAvailableMoves, UChessPiece* AllyPiece, IMovementRulesProvider* MovementProvider);

public:
	static ECheckmateStatus GetCheckmateStatusForPlayer(const UChessboardBase* Chessboard, const EColor PlayerColor, IMovementRulesProvider* MovementProvider);
	static bool IsKingInCheck(const UChessboardBase* Chessboard, const EColor Color);
};
