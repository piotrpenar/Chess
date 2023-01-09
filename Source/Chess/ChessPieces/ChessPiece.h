#pragma once
#include "CoreMinimal.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Enums/EColor.h"
#include "Chess/Enums/EFigure.h"
#include "Chess/Interfaces/TurnsProvider.h"
#include "Chess/Interfaces/ChessPieceMovement.h"
#include "Chess/Interfaces/MovementRulesProvider.h"
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
	bool bHasMoved = false;
	UPROPERTY()
	AChessFigure* ChessPieceActor;

public:
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	TScriptInterface<IMovementRulesProvider> MovementRules;
	UPROPERTY()
	TScriptInterface<ITurnsProvider> TurnsProvider;

	void Initialize(TScriptInterface<IMovementRulesProvider> SimulatedMovementRules, AChessFigure* ChessFigure);
	virtual void MoveToPosition(FIntPoint Position, FVector ActorPosition) override;
	virtual EFigure GetFigureType();
	virtual TArray<FMove> GetAvailableMoves() override;

	void SetPosition(FIntPoint Position);
	bool HasMoved() const;
	void SetColor(EColor PieceColor);
	void SetActorTransform(FTransform Transform) const;
	void SetActorPosition(FVector Position) const;
	void SetActorRotation(FRotator Rotation) const;
	EColor GetColor() const;
	FIntPoint GetBoardPosition();
	void DestroyActor() const;
};
