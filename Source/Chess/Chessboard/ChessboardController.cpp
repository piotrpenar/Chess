#include "ChessboardController.h"
#include "Chess/Controllers/ChessRulesController.h"
#include "Chess/ChessPieces/ChessPiece.h"
#include "Chess/ChessPieces/Logic/ChessPawn.h"
#include "Chess/Global/ChessGameState.h"


void UChessboardController::Initialize(UChessSceneUtilities* ChessSceneUtilitiesReference, UChessData* NewChessData, const TFunction<void(AChessFigure*)> FigureClickedCallback)
{
	this->ChessData = NewChessData;
	ChessboardTransformUtilities = ChessSceneUtilitiesReference;
	InitializeChessboard(FigureClickedCallback);
	CreateSimulatedChessboard();
	FinishChessboardsInitialization();
}

void UChessboardController::ResetChessboard() const
{
	Chessboard->ResetChessboard();
	SimulatedBoard->ResetChessboard();
	Chessboard->InitializeBoardPieces();
	FinishChessboardsInitialization();
}

void UChessboardController::InitializeChessboard(const TFunction<void(AChessFigure*)> FigureClickedCallback)
{
	Chessboard = ChessboardTransformUtilities->GetBoardWorld()->GetGameState<AChessGameState>()->GetChessboard();
	Chessboard->Initialize(ChessboardTransformUtilities, ChessData, FigureClickedCallback);
}

void UChessboardController::CreateSimulatedChessboard()
{
	SimulatedBoard = NewObject<USimulatedChessboard>();
}

void UChessboardController::FinishChessboardsInitialization() const
{
	Chessboard->InitializeMovementRules(SimulatedBoard);
	SimulatedBoard->InitializeSimulatedBoard(Chessboard);
}

void UChessboardController::AddChessPieceAtPosition(UChessPiece* ChessPiece, const FIntPoint Position) const
{
	Chessboard->SetPieceAtPosition(Position, ChessPiece);
	UChessPiece* SimulatedChessPiece = SimulatedBoard->CreateSimulatedChessPiece(ChessPiece);
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedChessPiece);
}

TScriptInterface<IMovementRulesProvider> UChessboardController::GetChessboardMovementRuleProvider() const
{
	return Chessboard->GetMovementRuleProvider();
}

UChessboard* UChessboardController::GetChessboard()
{
	return Chessboard;
}

void UChessboardController::SetupPiecesCallbacks(ITurnsProvider* TurnsProvider) const
{
	TArray<UChessPiece*> Pawns = Chessboard->GetChessPieces(EColor::White, EFigure::Pawn);
	Pawns.Append(Chessboard->GetChessPieces(EColor::Black, EFigure::Pawn));
	for (UChessPiece* ChessPiece : Pawns)
	{
		UChessPawn* Pawn = Cast<UChessPawn>(ChessPiece);
		Pawn->BindToTurnEndedEvent(TurnsProvider);
	}
}

void UChessboardController::RemoveChessPieceAtPosition(const FIntPoint Position) const
{
	Chessboard->SetPieceAtPosition(Position, nullptr);
	SimulatedBoard->SetPieceAtPosition(Position, nullptr);
}

void UChessboardController::MoveChessPieceToPosition(UChessPiece* ChessPiece, const FIntPoint Position) const
{
	const FIntPoint PreviousPosition = FIntPoint(ChessPiece->GetBoardPosition());
	if (!ChessPiece)
	{
		UE_LOG(LogTemp, Log, TEXT("Invalid Pawn!"));
		return;
	}
	ChessPiece->MoveToPosition(Position, ChessboardTransformUtilities->BoardToWorldTransform(Position).GetTranslation());
	Chessboard->MovePieceFromToPosition(ChessPiece, PreviousPosition, Position);
	UChessPiece* SimulatedChessPiece = SimulatedBoard->GetPieceAtPosition(PreviousPosition);
	SimulatedBoard->MovePieceFromToPosition(SimulatedChessPiece, PreviousPosition, Position);
}

void UChessboardController::HandleCastling(const FMove& Move, UChessPiece* ChessPiece) const
{
	UChessPiece* SourceChessPiece = Cast<UChessPiece>(Move.SourcePiece);
	const int Direction = FMath::Sign(SourceChessPiece->GetBoardPosition().X - ChessPiece->GetBoardPosition().X);
	const FIntPoint TargetPosition = Move.TargetPosition + FIntPoint(Direction, 0);
	MoveChessPieceToPosition(ChessPiece, TargetPosition);
}

void UChessboardController::HandleEnPassant(UChessPiece* ChessPiece) const
{
	RemoveChessPieceAtPosition(ChessPiece->GetBoardPosition());
}

void UChessboardController::PromotePawn(UChessPiece* ChessPiece, const EFigure TargetFigure) const
{
	const FIntPoint TargetPosition = ChessPiece->GetBoardPosition();
	const EColor Color = ChessPiece->GetColor();
	RemoveChessPieceAtPosition(ChessPiece->GetBoardPosition());
	UChessPiece* NewChessPiece = Chessboard->GenerateChessPieceAtPosition(TargetFigure, Color, TargetPosition);
	AddChessPieceAtPosition(NewChessPiece, TargetPosition);
}

//TODO: Add proper UI Implementation here. Currently we always switch for queen.
void UChessboardController::HandlePawnPromotion(const FMove& Move) const
{
	UChessPiece* Pawn = Cast<UChessPiece>(Move.SourcePiece);
	PromotePawn(Pawn, EFigure::Queen);
}

void UChessboardController::HandleSpecialMoveType(const FMove& Move) const
{
	UChessPiece* TargetChessPiece = Cast<UChessPiece>(Move.TargetObject);
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
