#pragma once
#include "piece.hpp"

class Pawn : public Piece
{
public:

	Pawn(const std::string_view& textureName);
};