// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessBoardProvider.h"

UObject* IChessBoardProvider:: GetPieceAtPosition(FVector2D BoardPosition)
{
	return nullptr;
}

FTransform IChessBoardProvider::BoardToWorldTransform(const int X, const int Y)
{
	return FTransform();
}

FTransform IChessBoardProvider::BoardToWorldTransform(FVector2D Position)
{
	return FTransform();
}

void IChessBoardProvider::SetPieceAtPosition(const FVector2D Vector2, UObject* ChessPiece)
{
}
