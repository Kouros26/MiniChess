#include "piece.hpp"
#include <iostream>

#include "SFML/Window/VideoMode.hpp"

Piece::Piece(const std::string_view& textureName)
{
	if (!texture.loadFromFile(std::string(TEXTURE_PATH) + textureName.data()))
	{
		std::cout << "Failed to load Piece texture" << '\n';

		return;
	}

	texture.setSmooth(true);

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.8f, 0.8f));

	const sf::VideoMode monitor = sf::VideoMode::getDesktopMode();
	const sf::Vector2f textureSize = sprite.getLocalBounds().getSize();
	sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite.setPosition(static_cast<float>(monitor.width) / 2.0f, static_cast<float>(monitor.height) / 2.0f);
}
