#include "board.hpp"

#include <iostream>

#include "SFML/Window/VideoMode.hpp"

Board::Board()
{
	if (!texture.loadFromFile(std::string(TEXTURE_PATH) + "Board.png"))
	{
		std::cout << "Failed to load Board texture" << '\n';

		return;
	}

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.3f, 0.3f));

	const sf::VideoMode monitor = sf::VideoMode::getDesktopMode();
	const sf::Vector2f textureSize = sprite.getLocalBounds().getSize();
	sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite.setPosition(static_cast<float>(monitor.width) / 2.0f, static_cast<float>(monitor.height) / 2.0f);
}
