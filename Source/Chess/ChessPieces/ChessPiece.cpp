#include "ChessPiece.h"

#include "Figures/AChessFigure.h"

void UChessPiece::SetColor(const EColor PieceColor)
{
	Color = PieceColor;
}

EFigure UChessPiece::GetFigureType()
{
	return EFigure::Invalid;
}

FIntPoint UChessPiece::GetBoardPosition()
{
	return BoardPosition;
}

void UChessPiece::SetAsSimulated(TScriptInterface<IMovementVerifier> SimulatedMovementVerifier)
{
	bIsSimulated = true;
	MovementVerifier = SimulatedMovementVerifier;
	ChessPieceActor = nullptr;
}

bool UChessPiece::IsSimulated()
{
	return bIsSimulated;
}

void UChessPiece::SetReferences(UChessData* NewChessData, TScriptInterface<IMovementVerifier> NewMovementVerifier, TScriptInterface<IChessGameState> NewGameState)
{
	this->ChessData = NewChessData;
	this->MovementVerifier = NewMovementVerifier;
	this->ChessGameState = NewGameState;
}

bool UChessPiece::CanMoveThisTurn()
{
	return ChessGameState->GetCurrentPlayer() == Color;
}

EColor UChessPiece::GetColor() const
{
	return Color;
}

TArray<FMove> UChessPiece::GetAvailableMoves()
{
	return {};
}

void UChessPiece::DestroyChessPiece() const
{
	if (ChessPieceActor && !bIsSimulated)
	{
		ChessPieceActor->Destroy();
	}
}

void UChessPiece::SetPosition(FIntPoint Position)
{
	this->BoardPosition = Position;
	if (!bIsSimulated)
	{
		ChessPieceActor->SetBoardPosition(Position);
	}
}

void UChessPiece::SetPosition(const int X, const int Y)
{
	SetPosition(FIntPoint(X, Y));
}

void UChessPiece::SetActorRotation(const FRotator Rotation) const
{
	if (ChessPieceActor)
	{
		ChessPieceActor->SetActorRotation(Rotation);
	}
}

void UChessPiece::SetActorPosition(const FVector Position) const
{
	if (ChessPieceActor)
	{
		ChessPieceActor->SetActorLocation(Position);
	}
}

void UChessPiece::SetActorTransform(const FTransform Transform) const
{
	if (ChessPieceActor)
	{
		ChessPieceActor->SetActorTransform(Transform);
	}
}

void UChessPiece::MoveToPosition(FIntPoint Position, FVector ActorPosition)
{
	BoardPosition = Position;
	if (ChessPieceActor)
	{
		ChessPieceActor->SetBoardPosition(Position);
		SetActorPosition(ActorPosition);
	}
}

void UChessPiece::CreateActor(UWorld* World, IBoardHighlighter* Highlighter)
{
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Log, TEXT("World is invalid"))
		return;
	}
	AChessFigure* Actor = World->SpawnActor<AChessFigure>(ChessData->GetChessFigureActor());
	if (!IsValid(Actor))
	{
		UE_LOG(LogTemp, Log, TEXT("Actor is invalid"))
		return;
	}
	UActorComponent* Component = Actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	if (!IsValid(Component))
	{
		UE_LOG(LogTemp, Log, TEXT("Component is invalid"))
		return;
	}
	if (!IsValid(ChessData))
	{
		UE_LOG(LogTemp, Log, TEXT("ChessData is invalid"))
		return;
	}

	UStaticMesh* Mesh = ChessData->GetMeshForType(GetFigureType());
	if (!IsValid(Mesh))
	{
		UE_LOG(LogTemp, Log, TEXT("Mesh is invalid"))
		return;
	}
	UStaticMeshComponent* StaticMeshComponent = static_cast<UStaticMeshComponent*>(Component);
	if (!IsValid(StaticMeshComponent))
	{
		UE_LOG(LogTemp, Log, TEXT("StaticMeshComponent is invalid"))
		return;
	}
	StaticMeshComponent->SetStaticMesh(Mesh);
	ChessPieceActor = Actor;
	Actor->Highlighter = Highlighter;
	Actor->SourcePiece = this;
#if WITH_EDITOR
	Actor->SetActorLabel(FString(UEnum::GetValueAsString(GetColor()) + " " + UEnum::GetValueAsString(GetFigureType())));
#endif
	
}
