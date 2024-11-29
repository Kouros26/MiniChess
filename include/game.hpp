#pragma once

#include "board.hpp"

namespace sf
{
	class RenderWindow;
}

class Game
{
	Board board;

public:

	Game();

	void DrawGameSprites(sf::RenderWindow& window);

	constexpr Board& GetBoard() { return board; }
};
