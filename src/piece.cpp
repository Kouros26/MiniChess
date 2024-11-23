#include "piece.hpp"
#include <iostream>

#include "SFML/Window/VideoMode.hpp"

std::string_view PieceTypeAsString(const PieceType type)
{
	switch (type)
	{
	case PieceType::Pawn:
		return "Pawn";

	case PieceType::Rook:
		return "Rook";

	case PieceType::Knight:
		return "Knight";

	case PieceType::Bishop:
		return "Bishop";

	case PieceType::Queen:
		return "Queen";

	case PieceType::King:
		return "King";
	}

	return "ERROR";
}

Piece::Piece(const PieceType pType, const Color pColor)
	: texture(std::make_shared<sf::Texture>()), type(pType), color(pColor)
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
