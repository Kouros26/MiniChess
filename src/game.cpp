#include "game.hpp"

#include "SFML/Graphics/RenderWindow.hpp"

Game::Game()
{

}

void Game::DrawGameSprites(sf::RenderWindow& window)
{
	board.Draw(window);
}
