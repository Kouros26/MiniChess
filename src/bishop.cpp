#include "bishop.hpp"

Bishop::Bishop(const Color pColor)
	: Piece(PieceType::Bishop, pColor)
{}

bool Bishop::CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY)
{
	return false;
}
