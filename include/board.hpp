#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Board
{
	sf::Sprite sprite;
	sf::Texture texture;

public:

	Board();

	constexpr sf::Sprite& GetSprite() { return sprite; }
};
