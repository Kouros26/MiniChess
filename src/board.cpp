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

	if (!spotTexture.loadFromFile(std::string(TEXTURE_PATH) + "Spot.png"))
	{
		std::cout << "Failed to load Spot texture" << '\n';

		return;
	}

	spotTexture.setSmooth(true);

	spotSprite.setTexture(spotTexture);
	spotSprite.setScale(sf::Vector2f(0.15f, 0.15f));
	const sf::VideoMode monitor = sf::VideoMode::getDesktopMode();
	sf::FloatRect textureSize = spotSprite.getLocalBounds();
	spotSprite.setOrigin(textureSize.width / 2, textureSize.height / 2);

	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.3f, 0.3f));

	textureSize = sprite.getLocalBounds();
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
		pieces.emplace_back(std::make_unique<Pawn>(color, x, y)); 
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Rook:
		pieces.emplace_back(std::make_unique<Rook>(color, x, y));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Knight:
		pieces.emplace_back(std::make_unique<Knight>(color, x, y));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Bishop:
		pieces.emplace_back(std::make_unique<Bishop>(color, x, y));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::Queen:
		pieces.emplace_back(std::make_unique<Queen>(color, x, y));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;

	case PieceType::King:
		pieces.emplace_back(std::make_unique<King>(color, x, y));
		grid[y][x].SetPieceOnSquare(*pieces[pieces.size() - 1]);
		break;
	}

	const sf::Vector2f boardPosition = sprite.getPosition();
	grid[y][x].GetPiece()->GetSprite().setPosition(boardPosition.x + xPieceOffset - xTileOffset * 4, boardPosition.y + yPieceOffset + yTileOffset * 3);
	MovePieceAt(*grid[y][x].GetPiece(), 0, 0, x, y);
}

sf::Vector2f Board::BoardCoordToPos(const BoardCoord coords)
{
	return sf::Vector2f(coords.x * xTileOffset, coords.y * yTileOffset);
}

std::vector<sf::Vector2f> Board::GetAvailableMovesPositions(Piece& piece)
{
	int8_t horizontal, vertical, diagonal;
	std::vector<sf::Vector2f> finalVector;
	BoardCoord coords = piece.GetBoardPosition();

	piece.GetUnrestrictedMoveCapabilities(horizontal, vertical, diagonal);


	if (horizontal == -1) // If infinite horizontal movement
	{
		for (int i = static_cast<int>(coords.x) - 1; i > 0; i--) // Check for left
		{
			finalVector.push_back(BoardCoordToPos({ .x = static_cast<uint8_t>(i), .y = coords.y }));
		}

		for (int i = static_cast<int>(coords.x) + 1; i < size; i++) // Check for right
		{
			finalVector.push_back(BoardCoordToPos({ .x = static_cast<uint8_t>(i), .y = coords.y }));
		}
	}

	if (vertical == -1) // If infinite vertical movement
	{
		for (int i = static_cast<int>(coords.y) - 1; i > 0; i--) // Check for down
		{
			finalVector.push_back(BoardCoordToPos({ .x = coords.x, .y = static_cast<uint8_t>(i) }));
		}

		//for (int i = coords.x + 1; i > size; i++) // Check for right
		//{
		//	finalVector.push_back(BoardCoordToPos({ .x = static_cast<uint8_t>(i), .y = coords.y }));
		//}
	}

	return finalVector;
}

//void Board::ShowAvailableMoves(sf::RenderWindow& window, Piece& piece) const
//{
//	uint8_t horizontal, vertical, diagonal;
//
//	piece.GetUnrestrictedMoveCapabilities(horizontal, vertical, diagonal);
//}

void Board::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);

	for (const auto& piece : pieces)
	{
		window.draw(piece->GetSprite());
	}

	if (selectedPiece != nullptr)
	{
		const auto moves = GetAvailableMovesPositions(*selectedPiece);

		for (const auto& move : moves)
		{
			spotSprite.setPosition(move.x, move.y);
			window.draw(spotSprite);
		}
	}
}

void Board::SelectClickedPiece(const sf::Vector2f& position)
{
	for (const auto& piece : pieces)
	{
		//TODO: if spot localbounds countains position, move piece to position

		if (piece->GetSprite().getGlobalBounds().contains(position))
		{
			selectedPiece = piece.get();
			std::cout << "Sprite " << PieceTypeAsString(piece->GetType()) << " clicked!" << '\n';

			return;
		}
	}

	selectedPiece = nullptr;
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
