#include "knight.hpp"

Knight::Knight(const Color pColor, const unsigned x, const unsigned y)
	: Piece(PieceType::Knight, pColor, x, y)
{}

bool Knight::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}

void Knight::GetUnrestrictedMoveCapabilities(int8_t& outHorizontal, int8_t& outVertical, int8_t& outDiagonal)
{
	outHorizontal = 0;
	outVertical = 0;
	outDiagonal = 0;
}
