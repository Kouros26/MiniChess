#include "pawn.hpp"

Pawn::Pawn(const Color pColor)
	: Piece(PieceType::Pawn, pColor)
{ }

bool Pawn::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}
