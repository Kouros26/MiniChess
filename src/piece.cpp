#include "piece.hpp"
#include <iostream>

#include "SFML/Window/VideoMode.hpp"

BoardCoord BoardCoord::operator+(const BoardCoord& second) const
{
	return BoardCoord(this->x + second.x, this->y + second.y );
}

BoardCoord BoardCoord::operator-(const BoardCoord& second) const
{
	return BoardCoord(this->x - second.x, this->y - second.y);
}

Piece::Piece(const PieceType pType, const Color pColor, const unsigned x, const unsigned y)
	: texture(std::make_shared<sf::Texture>()), type(pType), color(pColor),
	  boardPosition({.x = static_cast<int8_t>(x), .y = static_cast<int8_t>(y) })
{
	std::string_view extension = ".png";

	if (pColor == Color::Black)
	{
		extension = "_Black.png";
	}

	if (!texture->loadFromFile(std::string(TEXTURE_PATH) + PieceTypeAsString(pType).data() + extension.data()))
	{
		std::cout << "Failed to load Piece texture" << '\n';
		return;
	}

	texture->setSmooth(true);

	sprite.setTexture(*texture);
	sprite.setScale(sf::Vector2f(0.8f, 0.8f));

	const sf::VideoMode monitor = sf::VideoMode::getDesktopMode();
	const sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	sprite.setPosition(static_cast<float>(monitor.width) / 2.0f, static_cast<float>(monitor.height) / 2.0f);
}

void Piece::SetBoardPosition(const BoardCoord pNewPosition)
{
	boardPosition = pNewPosition;
}
