#include "pawn.hpp"

Pawn::Pawn(const Color pColor, const unsigned x, const unsigned y)
	: Piece(PieceType::Pawn, pColor, x, y)
{ }

bool Pawn::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}

void Pawn::GetUnrestrictedMoveCapabilities(int8_t& outHorizontal, int8_t& outVertical, int8_t& outDiagonal)
{
	outHorizontal = 0;
	outVertical = 1;
	outDiagonal = 0;
}
