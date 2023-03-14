#include "Chessboard.h"

#include "ChessboardMovementRules.h"
#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Interfaces/MovementRulesProvider.h"

void UChessboard::Initialize(UChessSceneUtilities* ChessSceneUtilitiesReference, UChessData* Data, const TFunction<void(AChessFigure*)> ExternalFigureClickedCallback)
{
	Super::Initialize(Data);
	ChessboardTransformUtilities = ChessSceneUtilitiesReference;
	World = ChessboardTransformUtilities->GetBoardWorld();
	FigureClickedCallback = ExternalFigureClickedCallback;
}

void UChessboard::InitializeBoardPieces()
{
	GenerateChessPieces(EColor::White);
	GenerateChessPieces(EColor::Black);
}

void UChessboard::InitializeMovementRules(USimulatedChessboard* SimulatedBoard)
{
	UChessboardMovementRules* MovementRules = NewObject<UChessboardMovementRules>();
	MovementRules->InitializeMovementRules(ChessData, this);
	MovementRules->SetSimulatedChessboard(SimulatedBoard);
	ChessboardMovementRules.SetObject(MovementRules);
	ChessboardMovementRules.SetInterface(Cast<IMovementRulesProvider>(MovementRules));
	GenerateEmptyBoard();
	InitializeBoardPieces();
}

void UChessboard::GenerateChessPieces(const EColor FigureColor)
{
	const bool bIsWhite = FigureColor == EColor::White;
	const int ManRow = bIsWhite ? 0 : 7;
	const int PawnRow = bIsWhite ? 1 : 6;
	TArray<EFigure> MenTargetArray = ChessData->GetMen();
	TArray<EFigure> Pawns = ChessData->GetPawns();
	GenerateChessRow(MenTargetArray, FigureColor, ManRow);
	GenerateChessRow(Pawns, FigureColor, PawnRow);
}

UChessPiece* UChessboard::GenerateChessPieceAtPosition(const EFigure Figure, const EColor Color, const FIntPoint Position)
{
	UChessPiece* ChessPiece = GenerateChessPiece(Figure);
	SetupChessPiece(ChessPiece, Color, Position);
	return ChessPiece;
}

void UChessboard::GenerateChessRow(TArray<EFigure>& Figures, const EColor Color, const int Y)
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
	ChessPiece->SetActorTransform(ChessboardTransformUtilities->GenerateChessPieceTransform(Position, Color));
}

TScriptInterface<IMovementRulesProvider> UChessboard::GetMovementRuleProvider() const
{
	return ChessboardMovementRules;
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
	const EFigure PieceFigure = SourceChessPiece->GetFigureType();
	const EColor PieceColor = SourceChessPiece->GetColor();
	if (!IsValid(ChessData))
	{
		UE_LOG(LogTemp, Warning, TEXT("ChessData is invalid"))
		return nullptr;
	}
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
	UStaticMesh* Mesh = ChessData->GetMeshForType(PieceFigure);
	if (!IsValid(Mesh))
	{
		UE_LOG(LogTemp, Warning, TEXT("Mesh is invalid"))
		return nullptr;
	}
	UMaterialInstance* Material = ChessData->GetMaterialForType(PieceFigure, PieceColor);
	if (!IsValid(Material))
	{
		UE_LOG(LogTemp, Warning, TEXT("Material is invalid"))
		return nullptr;
	}
	UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Component);
	if (!IsValid(StaticMeshComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticMeshComponent is invalid"))
		return nullptr;
	}
	StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->SetMaterial(0, Material);
	Actor->SetSourcePiece(SourceChessPiece);
	Actor->SetClickCallback(FigureClickedCallback);
	Actor->SetColor(PieceColor);
	Actor->AttachToActor(ChessBoardOrigin,FAttachmentTransformRules(EAttachmentRule::KeepWorld,false),FName());
#if WITH_EDITOR
	Actor->SetActorLabel(FString(UEnum::GetValueAsString(PieceColor) + " " + UEnum::GetValueAsString(PieceFigure)));
#endif
	return Actor;
}
