#include "rook.hpp"

Rook::Rook(const Color pColor, const unsigned x, const unsigned y)
	: Piece(PieceType::Rook, pColor, x, y)
{}

bool Rook::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}

void Rook::GetUnrestrictedMoveCapabilities(int8_t& outHorizontal, int8_t& outVertical, int8_t& outDiagonal)
{
	outHorizontal = 100;
	outVertical = 100;
	outDiagonal = 0;
}
