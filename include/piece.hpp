#pragma once
#include <memory>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

enum class PieceType : uint8_t
{
	Pawn = 0,
	Rook,
	Knight,
	Bishop,
	Queen,
	King,
};

enum class Color : uint8_t
{
	White = 0,
	Black
};

inline static std::string_view PieceTypeAsString(const PieceType type)
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

class Piece
{
protected:

	sf::Sprite sprite;
	std::shared_ptr<sf::Texture> texture;

	PieceType type = PieceType::Pawn;
	Color color = Color::White; 

public:

	Piece(const PieceType pType, const Color pColor);

	virtual ~Piece() = default;

	virtual bool CanMove(uint8_t fromX, uint8_t fromY, uint8_t toX, uint8_t toY) = 0;

	constexpr sf::Sprite& GetSprite() { return sprite; }
	constexpr PieceType GetType() const { return type; }
};
