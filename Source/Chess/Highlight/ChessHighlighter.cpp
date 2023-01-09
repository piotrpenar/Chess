#include "ChessHighlighter.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "Chess/Highlight/BoardHighlight.h"

void UChessHighlighter::Initialize(const TSubclassOf<ABoardHighlight> BoardHighlightSourceActor, UChessSceneUtilities* ChessSceneUtilitiesReference)
{
	BoardHighlightActor = BoardHighlightSourceActor;
	ChessboardTransformUtilities = ChessSceneUtilitiesReference;
}

void UChessHighlighter::SetSelectedFigure(AActor* SelectedFigureActor)
{
	AChessFigure* Figure = static_cast<AChessFigure*>(SelectedFigureActor);
	CurrentSelectedFigure = Figure;
}

void UChessHighlighter::HighlightSelected(ABoardHighlight* CheckerHighlight)
{
	ClearHighlights();
	const FMove TargetMove = CheckerHighlight->GetSourceMove();
	//Invoke Hightlight Selected
}
void UChessHighlighter::CreateHighlights(TArray<FMove> Moves)
{
	ClearHighlights();
	for (const FMove Move : Moves)
	{
		ABoardHighlight* Actor = ChessboardTransformUtilities->GetBoardWorld()->SpawnActor<ABoardHighlight>(BoardHighlightActor);
		Actor->SetActorTransform(ChessboardTransformUtilities->BoardToWorldTransform(Move.TargetPosition));
		Actor->Initialize(Move,CurrentSelectedFigure);
		Actor->OnHighlightClicked().BindUObject(this,&UChessHighlighter::HighlightSelected);
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



