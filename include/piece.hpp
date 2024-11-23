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
	None
};

enum class Color : uint8_t
{
	White = 0,
	Black
};

inline static std::string_view PieceTypeAsString(const PieceType type);

class Piece
{
	sf::Sprite sprite;
	std::shared_ptr<sf::Texture> texture;

	PieceType type = PieceType::Pawn;
	Color color = Color::White;

public:

	Piece(const PieceType pType, const Color pColor);

	constexpr sf::Sprite& GetSprite() { return sprite; }
	constexpr PieceType GetType() const { return type; }
};
