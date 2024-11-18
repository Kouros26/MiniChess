#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Piece
{
	sf::Sprite sprite;
	sf::Texture texture;

	uint8_t color = 0;

public:

	Piece(const std::string_view& textureName);

	constexpr sf::Sprite& GetSprite() { return sprite; }
};
