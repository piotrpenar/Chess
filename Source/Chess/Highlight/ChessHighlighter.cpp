#include "ChessHighlighter.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "Chess/Highlight/BoardHighlight.h"

void UChessHighlighter::Initialize(const TSubclassOf<ABoardHighlight> BoardHighlightSourceActor, UChessSceneUtilities* ChessSceneUtilitiesReference, TFunction<void(FMove*)> HighlightClickCallbackReference)
{
	BoardHighlightActor = BoardHighlightSourceActor;
	ChessboardTransformUtilities = ChessSceneUtilitiesReference;
	HighlightClickCallback = HighlightClickCallbackReference;
}

void UChessHighlighter::SetSelectedFigure(AActor* SelectedFigureActor)
{
	AChessFigure* Figure = static_cast<AChessFigure*>(SelectedFigureActor);
	CurrentSelectedFigure = Figure;
}

void UChessHighlighter::HighlightSelected(ABoardHighlight* CheckerHighlight)
{
	ClearHighlights();
	FMove Move = CheckerHighlight->GetSourceMove();
	UE_LOG(LogTemp, Log, TEXT("Callback called %s!"), *FString(Move.TargetPosition.ToString()))
	HighlightClickCallback(&Move);
}
void UChessHighlighter::CreateHighlights(TArray<FMove> Moves)
{
	ClearHighlights();
	for (const FMove Move : Moves)
	{
		ABoardHighlight* Actor = ChessboardTransformUtilities->GetBoardWorld()->SpawnActor<ABoardHighlight>(BoardHighlightActor);
		Actor->SetActorTransform(ChessboardTransformUtilities->BoardToWorldTransform(Move.TargetPosition));
		auto BoardHighlightClickedCallback = [this](ABoardHighlight* Highlight)
		{
			this->HighlightSelected(Highlight);
		};
		Actor->Initialize(Move,CurrentSelectedFigure,BoardHighlightClickedCallback);
		CurrentHighlights.Add(Actor);
	}
}

void UChessHighlighter::ClearHighlights()
{
	for (const auto Highlight : CurrentHighlights)
	{
		Highlight->Destroy();
	}
	CurrentHighlights.Empty();
}



