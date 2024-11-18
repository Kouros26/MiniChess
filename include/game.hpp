#pragma once
#include <vector>

#include "board.hpp"
#include "pawn.hpp"
#include "piece.hpp"


namespace sf
{
	class RenderWindow;
}

class Game
{
	Board board;

	std::vector<Piece*> pieces;
	Pawn testPawn;

public:

	Game();

	void DrawGameSprites(sf::RenderWindow& window);
};
