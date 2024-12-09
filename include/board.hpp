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
	std::vector<sf::Vector2f> pieceAvailableMoves{};

	uint16_t xFirstTile = 610;
	uint16_t yFirstTile = 890;

	uint8_t tileSize = 100;

	bool newSelectedPiece = false;

	void InitializeBoard(Color color);

	void CreatePiece(const PieceType type, const Color color, const int x, const int y);

	sf::Vector2f BoardCoordToPos(BoardCoord coords);
	sf::Vector2f BoardCoordToPos(const int x, const int y);

	BoardCoord PosToBoardCoord(sf::Vector2f pos);

	std::vector<sf::Vector2f> GetAvailableMovesPositions(Piece& piece);

	bool CheckSquare(std::vector<sf::Vector2f>& finalVector, const Color pieceColor, const int8_t x, const int8_t y);
	std::vector<sf::Vector2f> PawnMovement(Piece& piece);

	//void ShowAvailableMoves(sf::RenderWindow& window, Piece& piece) const;

public:

	Board();

	void Draw(sf::RenderWindow& window);

	void SelectClickedPiece(const sf::Vector2f& position);

	void MovePieceAt(Piece& piece, const BoardCoord coords);

	Piece*& GetPieceAt(const int8_t x, const int8_t y);
};