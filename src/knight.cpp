#include "knight.hpp"

Knight::Knight(const Color pColor)
	: Piece(PieceType::Knight, pColor)
{}

bool Knight::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}