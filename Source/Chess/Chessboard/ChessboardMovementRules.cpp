#include "ChessboardMovementRules.h"

#include "Chess/Controllers/ChessRulesController.h"

void UChessboardMovementRules::SetSimulatedChessboard(USimulatedChessboard* SimulatedChessboardReference)
{
	SimulatedChessboard = SimulatedChessboardReference;
}

bool UChessboardMovementRules::IsValidMove(const FIntPoint Position, UObject* ChessPieceObject)
{
	if (!ChessData->IsValidBoardPosition(Position))
	{
		return false;
	}
	UChessPiece* ChessPiece = Cast<UChessPiece>(ChessPieceObject);
	if (!ChessPiece)
	{
		UE_LOG(LogTemp, Log, TEXT("Cloud not cast to ChessPiece!"))
		return false;
	}
	return CanMoveInSimulation(Position, ChessPiece);
}


bool UChessboardMovementRules::CanMoveInSimulation(const FIntPoint Position, UChessPiece* ChessPiece) const
{
	const FIntPoint PreviousPosition = ChessPiece->GetBoardPosition();
	UChessPiece* SimulatedPiece = SimulatedChessboard->GetPieceAtPosition(PreviousPosition);
	UChessPiece* SimulatedTargetPiece = SimulatedChessboard->GetPieceAtPosition(Position);
	if (!SimulatedPiece)
	{
		UE_LOG(LogTemp, Log, TEXT("Cloud not find simulated piece in position %s"), *FString(PreviousPosition.ToString()))
		return false;
	}
	if (SimulatedTargetPiece && SimulatedTargetPiece->GetColor() == SimulatedPiece->GetColor())
	{
		return false;
	}
	SimulatedChessboard->SetPieceAtPosition(Position, SimulatedPiece);
	SimulatedChessboard->SetPieceAtPosition(PreviousPosition, nullptr);
	const bool bIsKingInCheck = UChessRulesController::IsKingInCheck(SimulatedChessboard, SimulatedPiece->GetColor());
	SimulatedChessboard->SetPieceAtPosition(PreviousPosition, SimulatedPiece);
	SimulatedChessboard->SetPieceAtPosition(Position, SimulatedTargetPiece);
	return !bIsKingInCheck;
}