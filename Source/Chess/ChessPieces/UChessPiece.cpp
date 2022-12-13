#include "UChessPiece.h"


void UChessPiece::SetColor(const EColor Color)
{
	this->Color = Color;
}

void UChessPiece::SetPosition(const int Row, const int Column)
{
	this->BoardPosition = UE::Geometry::FVector2i(Row,Column);
}

void 