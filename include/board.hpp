#pragma once
#include <array>
#include <optional>

#include "piece.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Board
{
	sf::Sprite sprite;
	sf::Texture texture;

	static constexpr uint8_t size = 8;

	std::array<std::array<std::optional<Piece>, size>, size> grid{};

	uint8_t xPieceOffset = 16;
	uint8_t yPieceOffset = 17;

	uint8_t xTileOffset = 85;
	uint8_t yTileOffset = 86;

	void InitializeBoard(Color color);

	void CreatePiece(const PieceType type, const Color color, const int x, const int y);

public:

	Board();

	void Draw(sf::RenderWindow& window);

	void MovePieceAt(Piece& piece, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo) const;

	Piece GetPieceAt(int x, int y);
};