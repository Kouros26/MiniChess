#pragma once

#include "piece.hpp"

class Square
{
	std::vector<Piece*> influenceList {};

	Piece* pieceOnSquare = nullptr;

public:

	~Square();

	constexpr Piece*& GetPiece() { return pieceOnSquare; }

	void SetPieceOnSquare(Piece& piece);

	void RegisterInfluence(Piece& piece);

	void RemoveInfluence(Piece& piece);
};
