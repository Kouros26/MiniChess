#include "rook.hpp"

Rook::Rook(const Color pColor)
	: Piece(PieceType::Rook, pColor)
{}

bool Rook::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}
