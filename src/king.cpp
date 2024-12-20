#include "king.hpp"

King::King(const Color pColor, const unsigned x, const unsigned y)
	: Piece(PieceType::King, pColor, x, y)
{}

bool King::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}

void King::GetUnrestrictedMoveCapabilities(int8_t& outHorizontal, int8_t& outVertical, int8_t& outDiagonal)
{
	outHorizontal = 1;
	outVertical = 1;
	outDiagonal = 1;
}
