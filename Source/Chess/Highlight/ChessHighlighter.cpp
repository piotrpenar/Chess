#include "ChessHighlighter.h"

#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/ChessPieces/Figures/ChessFigure.h"
#include "Chess/Highlight/BoardHighlight.h"

void UChessHighlighter::Initialize(const TSubclassOf<ABoardHighlight> BoardHighlightSourceActor, UChessSceneUtilities* ChessSceneUtilitiesReference,
                                   TFunction<void(FMove)> HighlightClickCallbackReference)
{
	BoardHighlightActor = BoardHighlightSourceActor;
	ChessboardTransformUtilities = ChessSceneUtilitiesReference;
	HighlightClickCallback = HighlightClickCallbackReference;
}

void UChessHighlighter::SetSelectedFigure(AActor* SelectedFigureActor)
{
	AChessFigure* Figure = Cast<AChessFigure>(SelectedFigureActor);
	CurrentSelectedFigure = Figure;
}

void UChessHighlighter::HighlightSelected(ABoardHighlight* CheckerHighlight)
{
	ClearHighlights();
	ClearPiecesHighlights();
	const FMove Move = CheckerHighlight->GetSourceMove();
	HighlightClickCallback(Move);
}

ABoardHighlight* UChessHighlighter::GetHighlightFromMove(const FMove& Move)
{
	for (const auto Highlight : CurrentHighlights)
	{
		if(Highlight->GetSourceMove().TargetPosition == Move.TargetPosition)
		{
			return Highlight;
		}
	}
	return nullptr;
}

void UChessHighlighter::ClearPiecesHighlights()
{
	for(const auto Figure : HighlightedFigures)
	{
		Figure->SetClickCallbackOverride(nullptr);
	}
	HighlightedFigures.Empty();
}

void UChessHighlighter::CreateHighlights(TArray<FMove>& Moves)
{
	ClearHighlights();
	for (const FMove Move : Moves)
	{
		ABoardHighlight* Actor = ChessboardTransformUtilities->GetBoardWorld()->SpawnActor<ABoardHighlight>(BoardHighlightActor);
		UE_LOG(LogTemp,Warning,TEXT("New Actor: %s"),*Actor->GetName());
		Actor->SetActorTransform(ChessboardTransformUtilities->BoardToWorldTransform(Move.TargetPosition));
		auto BoardHighlightClickedCallback = [this](ABoardHighlight* Highlight)
		{
			this->HighlightSelected(Highlight);
		};
		Actor->Initialize(Move, CurrentSelectedFigure, BoardHighlightClickedCallback);
		CurrentHighlights.Add(Actor);
	}
	UE_LOG(LogTemp,Warning,TEXT("Created %d highlights!"),CurrentHighlights.Num());
}

void UChessHighlighter::CreatePiecesHighlights(TArray<FMove>& Moves)
{
	ClearPiecesHighlights();
	for (const FMove Move : Moves)
	{
		if(!Move.TargetObject)
		{
			continue;
		}
		const UChessPiece* ChessPiece = StaticCast<UChessPiece*>(Move.TargetObject);
		AChessFigure* Figure = ChessPiece->GetActor();
		ABoardHighlight* SourceHighlight = GetHighlightFromMove(Move);
		auto PieceHighlightClickedCallback = [this,SourceHighlight]([[maybe_unused]] AChessFigure* SourceFigure)
		{
			if(!SourceHighlight)
			{
				UE_LOG(LogTemp,Warning,TEXT("SourceHighlight is nullptr!"));
			}
			this->HighlightSelected(SourceHighlight);
		};
		Figure->SetClickCallbackOverride(PieceHighlightClickedCallback);
		HighlightedFigures.Add(Figure);
	}
	UE_LOG(LogTemp,Warning,TEXT("Created %d pieces highlights!"),HighlightedFigures.Num());
}

void UChessHighlighter::ClearHighlights()
{
	for (const auto Highlight : CurrentHighlights)
	{
		Highlight->Destroy();
	}
	CurrentHighlights.Empty();
}
