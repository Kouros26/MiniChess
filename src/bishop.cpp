#include "bishop.hpp"

Bishop::Bishop(const Color pColor, const unsigned x, const unsigned y)
	: Piece(PieceType::Bishop, pColor, x, y)
{}

bool Bishop::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}

void Bishop::GetUnrestrictedMoveCapabilities(int8_t& outHorizontal, int8_t& outVertical, int8_t& outDiagonal)
{
	outHorizontal = 0;
	outVertical = 0;
	outDiagonal = -1;
}
