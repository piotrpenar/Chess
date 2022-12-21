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
	virtual void MoveToPosition(FVector2D Position) override;
	virtual EFigureType GetFigureType();
	virtual TArray<FMove> GetAvailableMoves() override;
	virtual bool CanMoveThisTurn() override;
	
	void SetColor(EColor PieceColor);
	void CreateActor(UWorld* World,IBoardHighlighter* Highlighter);
	void SetPosition(int X,int Y);
	void SetActorTransform(FTransform Transform) const;
	
	EColor GetColor() const;
	void DestroyChessPiece() const;
	
	FVector2D GetBoardPosition();
	UPROPERTY()
	UChessData* ChessData;
	UPROPERTY()
	TScriptInterface<IChessBoardProvider> BoardProvider;
	UPROPERTY()
	TScriptInterface<IChessGameState> ChessGameState;

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
