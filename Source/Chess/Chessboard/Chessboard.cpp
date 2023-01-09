#include "Chessboard.h"

#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Interfaces/MovementRulesProvider.h"

void UChessboard::Initialize(UChessData* Data, AActor* BoardOrigin, const TFunction<void(AChessFigure*)> ExternalFigureClickedCallback)
{
	ChessData = Data;
	ChessBoardOrigin = BoardOrigin;
	World = BoardOrigin->GetWorld();
	FigureClickedCallback = ExternalFigureClickedCallback;
	GenerateEmptyBoard();
	GenerateChessPieces(EColor::White);
	GenerateChessPieces(EColor::Black);
};

void UChessboard::InitializeMovementRules(USimulatedChessboard* SimulatedBoard)
{
	UChessboardMovementRules* MovementRules = NewObject<UChessboardMovementRules>();
	MovementRules->InitializeMovementRules(ChessData,this);
	MovementRules->SetSimulatedChessboard(SimulatedBoard);
	ChessboardMovementRules.SetObject(reinterpret_cast<UObject*>(MovementRules));
	ChessboardMovementRules.SetInterface(Cast<IMovementRulesProvider>(MovementRules));
}

void UChessboard::GenerateChessPieces(const EColor FigureColor)
{
	const bool bIsWhite = FigureColor == EColor::White;
	const int ManRow = bIsWhite ? 0 : 7;
	const int PawnRow = bIsWhite ? 1 : 6;
	TArray<EFigure> MenTargetArray = ChessData->GetMen();

	if (!bIsWhite)
	{
		Algo::Reverse(MenTargetArray);
	}

	GenerateChessRow(MenTargetArray, FigureColor, ManRow);
	GenerateChessRow(ChessData->GetPawns(), FigureColor, PawnRow);
}

UChessPiece* UChessboard::GenerateChessPieceAtPosition(const EFigure Figure, const EColor Color, const FIntPoint Position)
{
	UChessPiece* ChessPiece = GenerateChessPiece(Figure);
	SetupChessPiece(ChessPiece, Color, Position);
	return ChessPiece;
}

void UChessboard::GenerateChessRow(TArray<EFigure> Figures, const EColor Color, const int Y)
{
	for (int X = 0; X < ChessData->GetBoardSize(); X++)
	{
		const FIntPoint Position = FIntPoint(X, Y);
		UChessPiece* ChessPiece = GenerateChessPieceAtPosition(Figures[X], Color, Position);
		SetPieceAtPosition(Position, ChessPiece);
	}
}

UChessPiece* UChessboard::GenerateChessPiece(const EFigure Figure)
{
	return UChessPiecesFactory::GenerateChessPiece(Figure, this);
}

void UChessboard::SetupChessPiece(UChessPiece* ChessPiece, const EColor Color, const FIntPoint Position) const
{
	ChessPiece->SetColor(Color);
	ChessPiece->SetPosition(Position);
	AChessFigure* ChessFigure = CreateActorForChessPiece(ChessPiece);
	ChessPiece->Initialize(ChessboardMovementRules, ChessFigure);
	ChessPiece->SetActorTransform(GenerateChessPieceTransform(Position, Color));
}

FTransform UChessboard::GenerateChessPieceTransform(const FIntPoint Position, const EColor Color) const
{
	FTransform Transform = BoardToWorldTransform(Position);
	if (Color == EColor::Black)
	{
		FRotator Rotator = Transform.GetRotation().Rotator();
		Rotator.Yaw += 90;
		Transform.SetRotation(Rotator.Quaternion());
	}
	return Transform;
}

FTransform UChessboard::GetChessBoardTransform() const
{
	return ChessBoardOrigin->GetActorTransform();
}

FTransform UChessboard::BoardToWorldTransform(const FIntPoint Position) const
{
	FTransform Transform = GetChessBoardTransform();
	const float BoardDistance = ChessData->GetBoardCheckerSize();
	FVector PositionOffset = FVector(BoardDistance / 2 + Position.X * BoardDistance, BoardDistance / 2 + Position.Y * BoardDistance, ChessData->GetBoardOffset());
	PositionOffset = Transform.Rotator().RotateVector(PositionOffset);
	Transform.SetLocation(Transform.GetLocation() + PositionOffset);
	return Transform;
}

void UChessboard::SetPieceAtPosition(const FIntPoint Position, UChessPiece* ChessPiece)
{
	if (!ChessData->IsValidBoardPosition(Position))
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot set any object at %s"), *FString(Position.ToString()))
		return;
	}
	const UChessPiece* CurrentObject = GetPieceAtPosition(Position);
	if (CurrentObject)
	{
		CurrentObject->DestroyActor();
	}
	Super::SetPieceAtPosition(Position, ChessPiece);
}

AChessFigure* UChessboard::CreateActorForChessPiece(UChessPiece* SourceChessPiece) const
{
	AChessFigure* Actor = World->SpawnActor<AChessFigure>(ChessData->GetChessFigureActor());
	if (!IsValid(Actor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor is invalid"))
		return nullptr;
	}
	UActorComponent* Component = Actor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	if (!IsValid(Component))
	{
		UE_LOG(LogTemp, Warning, TEXT("Component is invalid"))
		return nullptr;
	}
	UStaticMesh* Mesh = ChessData->GetMeshForType(SourceChessPiece->GetFigureType());
	if (!IsValid(Mesh))
	{
		UE_LOG(LogTemp, Warning, TEXT("Mesh is invalid"))
		return nullptr;
	}
	UMaterialInstance* Material = ChessData->GetMaterialForType(SourceChessPiece->GetFigureType(), SourceChessPiece->GetColor());
	if (!IsValid(Material))
	{
		UE_LOG(LogTemp, Warning, TEXT("Material is invalid"))
		return nullptr;
	}
	UStaticMeshComponent* StaticMeshComponent = static_cast<UStaticMeshComponent*>(Component);
	if (!IsValid(StaticMeshComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent is invalid"))
		return nullptr;
	}
	StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->SetMaterial(0, Material);
	Actor->SetSourcePiece(SourceChessPiece);
	Actor->SetClickCallback(FigureClickedCallback);
#if WITH_EDITOR
	Actor->SetActorLabel(FString(UEnum::GetValueAsString(SourceChessPiece->GetColor()) + " " + UEnum::GetValueAsString(SourceChessPiece->GetFigureType())));
#endif
	return Actor;
}
