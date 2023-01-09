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
	Highlighter = NewObject<UChessHighlighter>();
	Highlighter->Initialize(ChessData->GetCheckerHighlightActor());
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
	TArray<EFigure> MenTargetArray = ChessData->GetMen();

	if (!bIsWhite)
	{
		Algo::Reverse(MenTargetArray);
	}

	GenerateChessRow(MenTargetArray, FigureColor, ManRow);
	GenerateChessRow(ChessData->GetPawns(), FigureColor, PawnRow);
}

void AChessController::SetupChessPiece(UChessPiece* ChessPiece, const EColor Color, const int X, int Y)
{
	ChessPiece->SetReferences(ChessData, ChessboardController, this);
	ChessPiece->SetColor(Color);
	ChessPiece->CreateActor(GetWorld());
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

void AChessController::PromotePawn(UChessPiece* ChessPiece, const EFigure TargetFigure)
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

