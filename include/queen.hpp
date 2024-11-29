#pragma once
#include "piece.hpp"

class Queen : public Piece
{
public:

	Queen(const Color pColor, const unsigned x, const unsigned y);

	bool CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY) override;
	void GetUnrestrictedMoveCapabilities(int8_t& outHorizontal, int8_t& outVertical, int8_t& outDiagonal) override;
};