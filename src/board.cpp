#include "board.hpp"

#include <iostream>

#include "SFML/Window/VideoMode.hpp"

Board::Board()
{
	if (!texture.loadFromFile(std::string(TEXTURE_PATH) + "Board.png"))
	{
		std::cout << "Failed to load Board texture" << '\n';

		return;
	}

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.3f, 0.3f));

	const sf::VideoMode monitor = sf::VideoMode::getDesktopMode();
	const sf::FloatRect textureSize = sprite.getLocalBounds();
	sprite.setOrigin(textureSize.width / 2, textureSize.height / 2);
	sprite.setPosition(static_cast<float>(monitor.width) / 2.0f, static_cast<float>(monitor.height) / 2.0f);

	InitializeBoard(Color::White);
	InitializeBoard(Color::Black);
}

void Board::InitializeBoard(Color color)
{
	CreatePiece(PieceType::Rook, color, 0, static_cast<int>(color) * (size - 1));
	CreatePiece(PieceType::Knight, color, 1, static_cast<int>(color) * (size - 1));
	CreatePiece(PieceType::Bishop, color, 2, static_cast<int>(color) * (size - 1));
	CreatePiece(PieceType::Queen, color, 3, static_cast<int>(color) * (size - 1));
	CreatePiece(PieceType::King, color, 4, static_cast<int>(color) * (size - 1));
	CreatePiece(PieceType::Bishop, color, 5, static_cast<int>(color) * (size - 1));
	CreatePiece(PieceType::Knight, color, 6, static_cast<int>(color) * (size - 1));
	CreatePiece(PieceType::Rook, color, 7, static_cast<int>(color) * (size - 1));

	for (int i = 0; i < size; i++)
	{
		CreatePiece(PieceType::Pawn, color, i, static_cast<int>(color) * 5 + 1);
	}
}

void Board::CreatePiece(const PieceType type, const Color color, const int x, const int y)
{
	grid[y][x] = Piece(type, color);
	const sf::Vector2f boardPosition = sprite.getPosition();
	grid[y][x].value().GetSprite().setPosition(boardPosition.x + xPieceOffset - xTileOffset * 4, boardPosition.y + yPieceOffset + yTileOffset * 3);
	MovePieceAt(grid[y][x].value(), 0, 0, x, y);
}

void Board::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	for (int height = 0; height < size; height++)
	{
		for (int width = 0; width < size; width++)
		{
			if (grid[height][width].has_value())
			{
				window.draw(grid[height][width].value().GetSprite());
			}
		}
	}
}

void Board::MovePieceAt(Piece& piece, const uint8_t xFrom, const uint8_t yFrom, const uint8_t xTo, const uint8_t yTo) const
{
	piece.GetSprite().move((xTo - xFrom) * xTileOffset, (yTo - yFrom) * -yTileOffset);
}

//Piece Board::GetPieceAt(int x, int y)
//{
//}
