#include "UChessPiece.h"


void UChessPiece::SetColor(const EColor PieceColor)
{
	Color = PieceColor;
}

void UChessPiece::SetPosition(const int Row, const int Column)
{
	this->BoardPosition = FVector2D(Row,Column);
}