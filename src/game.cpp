#include "game.hpp"

#include "pawn.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

Game::Game(): testPawn("Pawn.png")
{
	pieces.push_back(&testPawn);
}

void Game::DrawGameSprites(sf::RenderWindow& window)
{
	window.draw(board.GetSprite());

	for (const auto& i : pieces)
	{
		window.draw(i->GetSprite());
	}
}
