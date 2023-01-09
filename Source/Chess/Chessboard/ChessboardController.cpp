﻿#include "ChessboardController.h"
#include "Chess/Controllers/ChessRulesController.h"
#include "Chess/ChessPieces/ChessPiece.h"

void UChessboardController::Initialize(UChessboardTransformUtilities* ChessboardTransformUtilitiesReference,UChessData* NewChessData, AActor* ChessBoardOrigin, TFunction<void(AChessFigure*)> FigureClickedCallback)
{
	ChessboardTransformUtilities = ChessboardTransformUtilitiesReference;
	this->ChessData = NewChessData;
	Chessboard = NewObject<UChessboard>();
	Chessboard->Initialize(ChessData, ChessBoardOrigin,FigureClickedCallback);
	SimulatedBoard = NewObject<USimulatedChessboard>();
	SimulatedBoard->InitializeSimulatedBoard(ChessData,Chessboard);
	Chessboard->InitializeMovementRules(SimulatedBoard);
}

void UChessboardController::AddChessPieceAtPosition(UChessPiece* ChessPiece, const FIntPoint Position) const
{
	Chessboard->SetPieceAtPosition(Position, ChessPiece);
	UChessPiece* SimulatedChessPiece = SimulatedBoard->CreateSimulatedChessPiece(ChessPiece);
	SimulatedBoard->SetPieceAtPosition(Position, SimulatedChessPiece);
}
IMovementRulesProvider* UChessboardController::GetChessboardMovementRuleProvider() const
{
	return Chessboard->GetMovementRuleProvider();
}

void UChessboardController::RemoveChessPieceAtPosition(const FIntPoint Position) const
{
	Chessboard->SetPieceAtPosition(Position, nullptr);
	SimulatedBoard->SetPieceAtPosition(Position, nullptr);
}

void UChessboardController::MoveChessPieceToPosition(UChessPiece* ChessPiece, const FIntPoint Position) const
{
	const FIntPoint PreviousPosition = FIntPoint(ChessPiece->GetBoardPosition());
	ChessPiece->MoveToPosition(Position, ChessboardTransformUtilities->BoardToWorldTransform(Position).GetTranslation());
	Chessboard->MovePieceFromToPosition(ChessPiece, PreviousPosition, Position);
	UChessPiece* SimulatedChessPiece = SimulatedBoard->GetPieceAtPosition(PreviousPosition);
	SimulatedBoard->MovePieceFromToPosition(SimulatedChessPiece, PreviousPosition, Position);
}

void UChessboardController::HandleCastling(const FMove& Move, UChessPiece* ChessPiece) const
{
	UChessPiece* SourceChessPiece = static_cast<UChessPiece*>(Move.SourcePiece);
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
	UChessPiece* NewChessPiece = Chessboard->GenerateChessPieceAtPosition(TargetFigure,Color,TargetPosition);
	AddChessPieceAtPosition(NewChessPiece, TargetPosition);
}

//TODO: Add proper UI Implementation here. Currently we always switch for queen.
void UChessboardController::HandlePawnPromotion(const FMove& Move) const
{
	UE_LOG(LogTemp, Log, TEXT("Pawn Promotion!"));
	UChessPiece* Pawn = static_cast<UChessPiece*>(Move.SourcePiece);
	PromotePawn(Pawn, EFigure::Queen);
}

void UChessboardController::HandleSpecialMoveType(const FMove& Move) const
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
