#pragma once
#include "CoreMinimal.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/EColor.h"
#include "Chess/Enums/EFigure.h"
#include "Chess/Interfaces/TurnsProvider.h"
#include "Chess/Interfaces/ChessMovesProvider.h"
#include "Chess/Interfaces/ChessPieceMovement.h"
#include "Chess/Utils/FMove.h"
#include "ChessPiece.generated.h"

UCLASS()
class CHESS_API UChessPiece : public UObject, public IChessPieceMovement
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	EColor Color = EColor::White;
	UPROPERTY()
	FIntPoint BoardPosition;
	UPROPERTY()
	FVector3f WorldPosition;
	UPROPERTY()
	bool bIsSimulated = false;
	UPROPERTY()
	bool bHasMoved = false;
	UPROPERTY()
	AChessFigure* ChessPieceActor;

	void SetActorRotation(FRotator Rotation) const;
public:
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	TScriptInterface<IChessMovesProvider> MovementVerifier;
	UPROPERTY()
	TScriptInterface<ITurnsProvider> ChessGameState;

	virtual void MoveToPosition(FIntPoint Position, FVector ActorPosition) override;
	virtual EFigure GetFigureType();
	virtual TArray<FMove> GetAvailableMoves() override;
	virtual bool CanMoveThisTurn() override;

	bool HasMoved() const;
	void SetColor(EColor PieceColor);
	void SetPosition(int X, int Y);
	void SetActorTransform(FTransform Transform) const;
	void CreateActor(UWorld* World);
	void DestroyChessPiece() const;
	void SetPosition(FIntPoint Position);
	void SetActorPosition(FVector Position) const;
	EColor GetColor() const;
	FIntPoint GetBoardPosition();
	void SetAsSimulated(TScriptInterface<IChessMovesProvider> SimulatedMovementVerifier);
	bool IsSimulated() const;
	void SetReferences(UChessData* NewChessData, TScriptInterface<IChessMovesProvider> NewMovementVerifier, TScriptInterface<ITurnsProvider> NewGameState);
};
