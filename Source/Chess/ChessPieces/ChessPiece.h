#pragma once
#include "IntVectorTypes.h"
#include "Chess/Data/ChessData.h"
#include "Chess/Interfaces/ChessBoardProvider.h"
#include "Chess/Interfaces/ChessGameState.h"
#include "Chess/Interfaces/MovesProvider.h"
#include "Chess/Utils/EColor.h"
#include "Chess/Utils/EFigureType.h"
#include "Chess/Utils/FMove.h"
#include "ChessPiece.generated.h"

UCLASS()
class CHESS_API UChessPiece : public UObject, public IMovesProvider
{
	GENERATED_BODY()
public:
	void SetColor(EColor PieceColor);
	void CreateActor(UWorld* World,IBoardHighlighter* Highlighter);
	void SetPosition(int X,int Y);
	virtual void MoveToPosition(FVector2D Position) override;
	void SetActorTransform(FTransform Transform) const;
	
	virtual EFigureType GetFigureType();
	EColor GetColor() const;
	virtual TArray<FMove> GetAvailableMoves() override;
	void DestroyChessPiece() const;
	FVector2D GetBoardPosition();
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	TScriptInterface<IChessBoardProvider> BoardProvider;
	UPROPERTY()
	TScriptInterface<IChessGameState> ChessGameState;
	virtual bool CanMoveThisTurn() override;

protected:
	
	UPROPERTY()
	EColor Color = EColor::White;
	UPROPERTY()
	FVector2D BoardPosition;
	UPROPERTY()
	FVector3f WorldPosition;
	
private :
	UPROPERTY()
	AActor* ChessPieceActor;
	void SetActorPosition(FVector Position) const;
	void SetActorRotation(FRotator Rotation) const;
	void MoveActorToPosition(FVector2D Position) const;
};
