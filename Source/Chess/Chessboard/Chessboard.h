#pragma once
#include "CoreMinimal.h"
#include "ChessSceneUtilities.h"
#include "BaseClasses/ChessboardBase.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Simulation/SimulatedChessboard.h"
#include "Chessboard.generated.h"

UCLASS()
class CHESS_API UChessboard final : public UChessboardBase
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* ChessBoardOrigin;

	UPROPERTY()
	UWorld* World;

	UPROPERTY()
	UChessSceneUtilities* ChessboardTransformUtilities;

	TFunction<void(AChessFigure*)> FigureClickedCallback;

private:
	UChessPiece* GenerateChessPiece(EFigure Figure);
	AChessFigure* CreateActorForChessPiece(UChessPiece* SourceChessPiece) const;
	void GenerateChessRow(TArray<EFigure>& Figures, const EColor Color, const int Y);
	void GenerateChessPieces(EColor FigureColor);
	void SetupChessPiece(UChessPiece* ChessPiece, const EColor Color, FIntPoint Position) const;
	void InitializeBoardPieces();

public:
	void Initialize(UChessSceneUtilities* ChessSceneUtilitiesReference, UChessData* Data, const TFunction<void(AChessFigure*)> ExternalFigureClickedCallback);
	void InitializeMovementRules(USimulatedChessboard* SimulatedBoard);
	UChessPiece* GenerateChessPieceAtPosition(EFigure Figure, EColor Color, FIntPoint Position);
	virtual void SetPieceAtPosition(FIntPoint Position, UChessPiece* ChessPiece) override;
	TScriptInterface<IMovementRulesProvider> GetMovementRuleProvider() const;
};
