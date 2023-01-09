#include "ChessHighlighter.h"

#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/ChessPieces/Figures/AChessFigure.h"
#include "Chess/Highlight/BoardHighlight.h"

void UChessHighlighter::Initialize(const TSubclassOf<ABoardHighlight> BoardHighlightSourceActor)
{
	BoardHighlightActor = BoardHighlightSourceActor;
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
	UChessPiece* SourcePiece = static_cast<UChessPiece*>(TargetMove.SourcePiece);
	UChessPiece* TargetPiece = static_cast<UChessPiece*>(TargetMove.TargetObject);
	const FIntPoint TargetPosition = TargetMove.TargetPosition;
	//ChessboardController->MoveChessPieceToPosition(SourcePiece, TargetPosition);
	if (TargetMove.MoveType != EMoveType::Standard)
	{
		//HandleSpecialMoveType(TargetMove);
	}
}
void UChessHighlighter::CreateHighlights(TArray<FMove> Moves)
{
	ClearHighlights();
	for (const FMove Move : Moves)
	{
		ABoardHighlight* Actor = GetWorld()->SpawnActor<ABoardHighlight>();
		//SetActorTransform(Chessboard->BoardToWorldTransform(Move.TargetPosition.X, Move.TargetPosition.Y));
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



