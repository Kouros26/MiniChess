#include "board.hpp"

#include <iostream>

#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
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
	switch (type)
	{
	case PieceType::Pawn:
		pieces.emplace_back(std::make_unique<Pawn>(color)); 
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Rook:
		pieces.emplace_back(std::make_unique<Rook>(color));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Knight:
		pieces.emplace_back(std::make_unique<Knight>(color));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Bishop:
		pieces.emplace_back(std::make_unique<Bishop>(color));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Queen:
		pieces.emplace_back(std::make_unique<Queen>(color));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::King:
		pieces.emplace_back(std::make_unique<King>(color));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;
	}

	const sf::Vector2f boardPosition = sprite.getPosition();
	grid[y][x].GetPiece()->GetSprite().setPosition(boardPosition.x + xPieceOffset - xTileOffset * 4, boardPosition.y + yPieceOffset + yTileOffset * 3);
	MovePieceAt(*grid[y][x].GetPiece(), 0, 0, x, y);
}

void Board::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	for (int height = 0; height < size; height++)
	{
		for (int width = 0; width < size; width++)
		{
			if (grid[height][width].GetPiece() != nullptr)
			{
				window.draw(grid[height][width].GetPiece()->GetSprite());
			}
		}
	}
}

void Board::SelectClickedPiece(const sf::Vector2f& position) const
{
	for (const auto& piece : pieces)
	{
		if (piece->GetSprite().getGlobalBounds().contains(position))
		{
			std::cout << "Sprite " << PieceTypeAsString(piece->GetType()) << " clicked!" << '\n';

			return;
		}
	}

	std::cout << "No Sprite" << '\n';
}

void Board::MovePieceAt(Piece& piece, const uint8_t xFrom, const uint8_t yFrom, const uint8_t xTo, const uint8_t yTo) const
{
	piece.GetSprite().move((xTo - xFrom) * xTileOffset, (yTo - yFrom) * -yTileOffset);
}

Piece& Board::GetPieceAt(const uint8_t x, const uint8_t y)
{
	return *grid[y][x].GetPiece();
}
