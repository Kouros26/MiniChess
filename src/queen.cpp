#include "queen.hpp"

Queen::Queen(const Color pColor)
	: Piece(PieceType::Queen, pColor)
{}

bool Queen::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}
