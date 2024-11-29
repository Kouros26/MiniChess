#pragma once
#include "piece.hpp"

class Queen : public Piece
{
public:

	Queen(const Color pColor);

	bool CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY) override;
};

