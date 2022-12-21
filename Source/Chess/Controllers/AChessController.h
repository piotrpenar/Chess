// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChessRulesController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Interfaces/BoardHighlighter.h"
#include "Chess/Interfaces/ChessBoardProvider.h"
#include "Chess/Interfaces/ChessGameState.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/F2DBoardArray.h"
#include "AChessController.generated.h"

/**
 * 
*/
UCLASS(Blueprintable)
class CHESS_API AChessController : public AActor , public IChessBoardProvider, public IBoardHighlighter, public IChessGameState
{
	GENERATED_BODY()

public:
	void CreateChessPiece();
	void CreateFigures(const EColor FigureColor);
	UChessPiece* GenerateChessPiece(const EFigureType Figure);
	
	virtual FTransform BoardToWorldTransform(const int X, const int Y) override;
	virtual FTransform BoardToWorldTransform(FVector2D Position) override;
	virtual UObject* GetPieceAtPosition(FVector2D BoardPosition) override;
	virtual void SetPieceAtPosition(const FVector2D Vector2, UObject* ChessPiece) override;
	virtual bool IsValidMove(const FVector2D Position, UObject* ChessPiece) override;
	virtual void EndTurn() override;
	virtual void CreateHighlights(TArray<FMove> Moves) override;
	virtual void SetSelectedFigure(AActor* Figure) override;
	virtual void HighlightSelected(AActor* Source) override;
	virtual TArray<UChessPiece*> GetAllPiecesOfColor(const EColor Color) override;
	virtual UChessPiece* GetChessPiece(EFigureType Figure, EColor Color) override;
	virtual EColor GetCurrentPlayer() override;
	void SetPieceAtSimulatedPosition(const FVector2D Vector2, UObject* ChessPiece,TArray<F2DBoardArray>& BoardOverrideReference);
	void ClearHighlights();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UChessData* ChessData;
	
	UPROPERTY(EditAnywhere)
	AActor* ChessBoardOrigin;
	
private:
	UPROPERTY()
	TArray<F2DBoardArray> Board;

	UPROPERTY()
	UChessRulesController* RulesController;

	UPROPERTY()
	TMap<EFigureType, UChessPiece*> FigureTypeMap;
	UPROPERTY()
	TArray<AActor*> CurrentHighlights;
	UPROPERTY()
	AChessFigure* CurrentSelectedFigure;
	
	EColor CurrentPlayer = EColor::White;
	FTransform GetChessBoardTransform() const;
	FTransform GenerateChessPieceTransform(int TargetRow, int TargetColumn, EColor Color);
	void GenerateChessRow(TArray<EFigureType> Figures, const EColor Color, const int TargetRow);
	
	const TArray<EFigureType> Pawns = {
		EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn, EFigureType::Pawn,
		EFigureType::Pawn, EFigureType::Pawn
	};
	const TArray<EFigureType> Men = {
		EFigureType::Rook, EFigureType::Knight, EFigureType::Bishop, EFigureType::King, EFigureType::Queen, EFigureType::Bishop,
		EFigureType::Knight, EFigureType::Rook
	};
	
};
