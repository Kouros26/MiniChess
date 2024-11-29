#pragma once
#include <array>
#include <optional>

#include "piece.hpp"
#include "square.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Board
{
	sf::Sprite sprite;
	sf::Texture texture;

	sf::Sprite spotSprite;
	sf::Texture spotTexture;

	static constexpr uint8_t size = 8;

	std::vector<std::unique_ptr<Piece>> pieces;

	std::array<std::array<Square, size>, size> grid{};

	Piece* selectedPiece = nullptr;

	uint8_t xPieceOffset = 16;
	uint8_t yPieceOffset = 17;

	uint8_t xTileOffset = 85;
	uint8_t yTileOffset = 86;

	void InitializeBoard(Color color);

	void CreatePiece(const PieceType type, const Color color, const int x, const int y);

	sf::Vector2f BoardCoordToPos(BoardCoord coords);

	std::vector<sf::Vector2f> GetAvailableMovesPositions(Piece& piece);

	//void ShowAvailableMoves(sf::RenderWindow& window, Piece& piece) const;

public:

	Board();

	void Draw(sf::RenderWindow& window);

	void SelectClickedPiece(const sf::Vector2f& position);

	void MovePieceAt(Piece& piece, uint8_t xFrom, uint8_t yFrom, uint8_t xTo, uint8_t yTo) const;

	Piece& GetPieceAt(const uint8_t x, const uint8_t y);
};