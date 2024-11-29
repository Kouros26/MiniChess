#include "square.hpp"

Square::~Square()
{
	influenceList.clear();
	pieceOnSquare = nullptr;
}

void Square::SetPieceOnSquare(Piece& piece)
{
	pieceOnSquare = &piece;
}

void Square::RegisterInfluence(Piece& piece)
{
	influenceList.push_back(&piece);
}

void Square::RemoveInfluence(Piece& piece)
{
	influenceList.erase(std::ranges::find(influenceList, &piece));
}
