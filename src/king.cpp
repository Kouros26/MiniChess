#include "king.hpp"

King::King(const Color pColor)
	: Piece(PieceType::King, pColor)
{}

bool King::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}