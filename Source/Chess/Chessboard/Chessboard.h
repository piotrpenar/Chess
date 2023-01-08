#pragma once
#include "CoreMinimal.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigure.h"
#include "Chess/Utils/F2DBoardArray.h"
#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chessboard.generated.h"

UCLASS()
class CHESS_API UChessboard final : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	AActor* ChessBoardOrigin;
	UPROPERTY()
	TArray<F2DBoardArray> Board;
	UPROPERTY()
	bool bIsSimulation;

public:
	void Initialize(UChessData* Data, AActor* NewChessBoardOrigin);
	void SetPieceAtPosition(const FIntPoint Position, UChessPiece* ChessPiece);
	void MovePieceFromToPosition(UChessPiece* ChessPiece, FIntPoint FromPosition, FIntPoint ToPosition);
	void GenerateEmptyBoard();
	UChessPiece* GetPieceAtPosition(FIntPoint BoardPosition);
	FTransform BoardToWorldTransform(const int X, const int Y) const;
	FTransform BoardToWorldTransform(FIntPoint Position) const;
	FTransform GetChessBoardTransform() const;
	TArray<UChessPiece*> GetAllPiecesOfColor(const EColor Color);
	UChessPiece* GetChessPiece(const EFigure Figure, const EColor Color);
	UChessPiece* CreateSimulatedChessPiece(TScriptInterface<IMovementVerifier> SimulatedMovementVerifier, UChessPiece* ChessPiece);
	void SetAsSimulated(UChessboard* OriginalBoard, TScriptInterface<IMovementVerifier> SimulatedMovementVerifier);
};
