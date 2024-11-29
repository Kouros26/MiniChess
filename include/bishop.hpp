#pragma once
#include "piece.hpp"

class Bishop : public Piece
{
public:

	Bishop(const Color pColor);

	bool CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY) override;
};