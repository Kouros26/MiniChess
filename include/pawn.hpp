#pragma once
#include "piece.hpp"

class Pawn : public Piece
{
public:

	Pawn(const Color color);

	bool CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY) override;
};