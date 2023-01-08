#include "ChessController.h"
#include "Chess/Chessboard/ChessboardController.h"
#include "Chess/Chessboard/Chessboard.h"
#include "Chess/Helpers/ChessPiecesFactory.h"
#include "Chess/Enums/EColor.h"
#include "Chess/Enums/EFigure.h"
#include "Chess/Enums/EMoveType.h"


void AChessController::BeginPlay()
{
	Super::BeginPlay();
	RulesController = NewObject<UChessRulesController>();
	Chessboard = NewObject<UChessboard>();
	Chessboard->Initialize(ChessData, ChessBoardOrigin);
	Chessboard->GenerateEmptyBoard();
	ChessboardController = NewObject<UChessboardController>();
	ChessboardController->Initialize(ChessData, Chessboard, this);
	GenerateChessPieces(EColor::White);
	GenerateChessPieces(EColor::Black);
	ChessboardController->CreateChessboardSimulation();
}

void AChessController::GenerateChessPieces(const EColor FigureColor)
{
	const bool bIsWhite = FigureColor == EColor::White;
	const int ManRow = bIsWhite ? 0 : 7;
	const int PawnRow = bIsWhite ? 1 : 6;
	TArray<EFigure> MenTargetArray = Men;

	if (!bIsWhite)
	{
		Algo::Reverse(MenTargetArray);
	}

	GenerateChessRow(MenTargetArray, FigureColor, ManRow);
	GenerateChessRow(Pawns, FigureColor, PawnRow);
}

void AChessController::SetupChessPiece(UChessPiece* ChessPiece, const EColor Color, const int X, int Y)
{
	ChessPiece->SetReferences(ChessData, ChessboardController, this);
	ChessPiece->SetColor(Color);
	ChessPiece->CreateActor(GetWorld(), this);
	ChessPiece->SetPosition(X, Y);
	ChessPiece->SetActorTransform(GenerateChessPieceTransform(X, Y, Color));
}

void AChessController::GenerateChessRow(TArray<EFigure> Figures, const EColor Color, const int Y)
{
	for (int X = 0; X < ChessData->GetBoardSize(); X++)
	{
		UChessPiece* ChessPiece = GenerateChessPiece(Figures[X]);
		SetupChessPiece(ChessPiece, Color, X, Y);
		Chessboard->SetPieceAtPosition(FIntPoint(X, Y), ChessPiece);
	}
}

void AChessController::BroadcastTurnEnded(EColor Color) const
{
	TurnEndedEvent.Broadcast(Color);
}

UChessPiece* AChessController::GenerateChessPiece(const EFigure Figure)
{
	return UChessPiecesFactory::GenerateChessPiece(Figure, this);
}

FTransform AChessController::GenerateChessPieceTransform(const int X, const int Y, const EColor Color) const
{
	FTransform Transform = Chessboard->BoardToWorldTransform(X, Y);
	if (Color == EColor::Black)
	{
		FRotator Rotator = Transform.GetRotation().Rotator();
		Rotator.Yaw += 90;
		Transform.SetRotation(Rotator.Quaternion());
	}
	return Transform;
}


void AChessController::EndTurn()
{
	const EColor CurrentPlayerColor = CurrentPlayer;
	const EColor EnemyPlayer = CurrentPlayer == EColor::Black ? EColor::White : EColor::Black;
	if (CurrentPlayer == EColor::White)
	{
		CurrentPlayer = EColor::Black;
	}
	else
	{
		CurrentPlayer = EColor::White;
	}
	const ECheckmateStatus Status = RulesController->GetBoardStatusForColor(Chessboard, EnemyPlayer, ChessboardController);
	const FString Value = UEnum::GetValueAsString(Status);
	BroadcastTurnEnded(CurrentPlayerColor);
	UE_LOG(LogTemp, Log, TEXT("Check mate status is %s"), *FString(Value));
}

void AChessController::SetSelectedFigure(AActor* SelectedFigureActor)
{
	AChessFigure* Figure = static_cast<AChessFigure*>(SelectedFigureActor);
	CurrentSelectedFigure = Figure;
}

void AChessController::HandleCastling(const FMove& Move, UChessPiece* ChessPiece) const
{
	UChessPiece* SourceChessPiece = static_cast<UChessPiece*>(Move.SourcePiece);
	const int Direction = FMath::Sign(SourceChessPiece->GetBoardPosition().X - ChessPiece->GetBoardPosition().X);
	const FIntPoint TargetPosition = Move.TargetPosition + FIntPoint(Direction, 0);
	ChessboardController->MoveChessPieceToPosition(ChessPiece, TargetPosition);
}

void AChessController::HandleEnPassant(UChessPiece* ChessPiece) const
{
	ChessboardController->RemoveChessPieceAtPosition(ChessPiece->GetBoardPosition());
}

void AChessController::PromotePawn(UChessPiece* ChessPiece, EFigure TargetFigure)
{
	UChessPiece* NewFigure = UChessPiecesFactory::GenerateChessPiece(TargetFigure, this);
	const FIntPoint TargetPos = ChessPiece->GetBoardPosition();
	SetupChessPiece(NewFigure, ChessPiece->GetColor(), TargetPos.X, TargetPos.Y);
	ChessboardController->RemoveChessPieceAtPosition(ChessPiece->GetBoardPosition());
	ChessboardController->AddChessPieceAtPosition(NewFigure, TargetPos);
}

//TODO: Add proper UI Implementation here. Currently we always switch for queen.
void AChessController::HandlePawnPromotion(const FMove& Move)
{
	UE_LOG(LogTemp, Log, TEXT("Pawn Promotion!"));
	UChessPiece* Pawn = static_cast<UChessPiece*>(Move.SourcePiece);
	PromotePawn(Pawn, EFigure::Queen);
}

void AChessController::HandleSpecialMoveType(const FMove& Move)
{
	UE_LOG(LogTemp, Log, TEXT("Is special move!"));
	UChessPiece* TargetChessPiece = static_cast<UChessPiece*>(Move.TargetObject);
	switch (Move.MoveType)
	{
	case EMoveType::DoubleMove:
		break;
	case EMoveType::EnPassant:
		HandleEnPassant(TargetChessPiece);
		break;
	case EMoveType::Castling:
		HandleCastling(Move, TargetChessPiece);
		break;
	case EMoveType::PawnPromotion:
		HandlePawnPromotion(Move);
		break;
	default: ;
	}
}

void AChessController::HighlightSelected(AActor* Source)
{
	ClearHighlights();
	const ACheckerHighlight* CheckerHighlight = static_cast<ACheckerHighlight*>(Source);
	const FMove TargetMove = CheckerHighlight->Move;
	UChessPiece* SourcePiece = static_cast<UChessPiece*>(TargetMove.SourcePiece);
	UChessPiece* TargetPiece = static_cast<UChessPiece*>(TargetMove.TargetObject);
	const FIntPoint TargetPosition = TargetMove.TargetPosition;
	ChessboardController->MoveChessPieceToPosition(SourcePiece, TargetPosition);
	if (TargetMove.MoveType != EMoveType::Standard)
	{
		HandleSpecialMoveType(TargetMove);
	}
}

void AChessController::ClearHighlights()
{
	for (const auto Highlight : CurrentHighlights)
	{
		Highlight->Destroy();
	}
	CurrentHighlights.Empty();
}

AChessController::FTurnEnded& AChessController::OnTurnEnded()
{
	return TurnEndedEvent;
}

void AChessController::CreateHighlights(TArray<FMove> Moves)
{
	UE_LOG(LogTemp, Log, TEXT("Generating highlights"))
	ClearHighlights();
	for (const auto Move : Moves)
	{
		ACheckerHighlight* Actor = GetWorld()->SpawnActor<ACheckerHighlight>(ChessData->GetCheckerHighlightActor());
		Actor->SetActorTransform(Chessboard->BoardToWorldTransform(Move.TargetPosition.X, Move.TargetPosition.Y));
		Actor->Position = Move.TargetPosition;
		Actor->Highlighter = this;
		Actor->SourceFigure = CurrentSelectedFigure;
		Actor->Move = Move;
		CurrentHighlights.Add(Actor);
	}
}

EColor AChessController::GetCurrentPlayer()
{
	return CurrentPlayer;
}
