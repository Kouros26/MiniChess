#include "board.hpp"

#include <algorithm>
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
	sprite.setScale(sf::Vector2f(0.5f, 0.5f));

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
		grid[y][x].SetPieceOnSquare(pieces[pieces.size() - 1].get());
		break;

	case PieceType::Rook:
		pieces.emplace_back(std::make_unique<Rook>(color, x, y));
		grid[y][x].SetPieceOnSquare(pieces[pieces.size() - 1].get());
		break;

	case PieceType::Knight:
		pieces.emplace_back(std::make_unique<Knight>(color, x, y));
		grid[y][x].SetPieceOnSquare(pieces[pieces.size() - 1].get());
		break;

	case PieceType::Bishop:
		pieces.emplace_back(std::make_unique<Bishop>(color, x, y));
		grid[y][x].SetPieceOnSquare(pieces[pieces.size() - 1].get());
		break;

	case PieceType::Queen:
		pieces.emplace_back(std::make_unique<Queen>(color, x, y));
		grid[y][x].SetPieceOnSquare(pieces[pieces.size() - 1].get());
		break;

	case PieceType::King:
		pieces.emplace_back(std::make_unique<King>(color, x, y));
		grid[y][x].SetPieceOnSquare(pieces[pieces.size() - 1].get());
		break;
	}

	grid[y][x].GetPiece()->GetSprite().setPosition(BoardCoordToPos(x, y));
}

sf::Vector2f Board::BoardCoordToPos(const BoardCoord coords)
{
	return sf::Vector2f(coords.x * tileSize + xFirstTile, yFirstTile - coords.y * tileSize );
}

sf::Vector2f Board::BoardCoordToPos(const int x, const int y)
{
	return sf::Vector2f(x * tileSize + xFirstTile, yFirstTile - y * tileSize);
}

BoardCoord Board::PosToBoardCoord(const sf::Vector2f pos)
{
	BoardCoord coords;
	coords.x = static_cast<int8_t>((pos.x - xFirstTile) / tileSize);
	coords.y = static_cast<int8_t>((yFirstTile - pos.y) / tileSize);
	return coords;
}

std::vector<sf::Vector2f> Board::GetAvailableMovesPositions(Piece& piece)
{
	int8_t horizontal, vertical, diagonal;
	std::vector<sf::Vector2f> finalVector;
	BoardCoord coords = piece.GetBoardPosition();
	Color pieceColor = piece.GetColor();

	piece.GetUnrestrictedMoveCapabilities(horizontal, vertical, diagonal);

	if (piece.GetType() == PieceType::Pawn)
	{
		return PawnMovement(piece);
	}

	if (piece.GetType() == PieceType::Knight)
	{
		BoardCoord piecePos = piece.GetBoardPosition();
		CheckSquare(finalVector, pieceColor,piecePos.x - 1, piecePos.y + 2);
		CheckSquare(finalVector, pieceColor, piecePos.x + 1, piecePos.y + 2);

		CheckSquare(finalVector, pieceColor, piecePos.x - 1, piecePos.y - 2);
		CheckSquare(finalVector, pieceColor, piecePos.x + 1, piecePos.y - 2);

		CheckSquare(finalVector, pieceColor, piecePos.x - 2, piecePos.y + 1);
		CheckSquare(finalVector, pieceColor, piecePos.x - 2, piecePos.y - 1);

		CheckSquare(finalVector, pieceColor, piecePos.x + 2, piecePos.y + 1);
		CheckSquare(finalVector, pieceColor, piecePos.x + 2, piecePos.y - 1);

		return finalVector;
	}

	int8_t horizontalCopy = horizontal;
	for (int8_t i = coords.x - 1; i >= 0 && horizontalCopy > 0; i--, horizontalCopy--) // Check for left
	{
		if (!CheckSquare(finalVector, pieceColor, i, coords.y))
			break;
	}

	horizontalCopy = horizontal;
	for (int8_t i = coords.x + 1; i < size && horizontalCopy > 0; i++, horizontalCopy--) // Check for right
	{
		if (!CheckSquare(finalVector, pieceColor, i, coords.y))
			break;
	}

	int8_t verticalCopy = vertical;
	for (int8_t i = coords.y - 1; i >= 0 && verticalCopy > 0; i--, verticalCopy--) // Check for down
	{
		if (!CheckSquare(finalVector, pieceColor, coords.x, i))
			break;
	}

	verticalCopy = vertical;
	for (int8_t i = coords.y + 1; i < size && verticalCopy > 0; i++, verticalCopy--) // Check for up
	{
		if (!CheckSquare(finalVector, pieceColor, coords.x, i))
			break;
	}

	int8_t diagonalCopy = diagonal;
	for (BoardCoord coordsIncr = coords + BoardCoord{ .x = -1, .y = 1};
		 coordsIncr.x >= 0 && coordsIncr.y < size && diagonalCopy > 0;
		 coordsIncr = coordsIncr + BoardCoord{ .x = -1, .y = 1 }, diagonalCopy--) // Check for up-left
	{
		if (!CheckSquare(finalVector, pieceColor, coordsIncr.x, coordsIncr.y))
			break;
	}

	diagonalCopy = diagonal;
	for (BoardCoord coordsIncr = coords + BoardCoord{ .x = 1, .y = 1 };
		coordsIncr.x < size && coordsIncr.y < size && diagonalCopy > 0;
		coordsIncr = coordsIncr + BoardCoord{ .x = 1, .y = 1 }, diagonalCopy--) // Check for up-right
	{
		if (!CheckSquare(finalVector, pieceColor, coordsIncr.x, coordsIncr.y))
			break;
	}

	diagonalCopy = diagonal;
	for (BoardCoord coordsIncr = coords - BoardCoord{ .x = 1, .y = 1 };
		coordsIncr.x >= 0 && coordsIncr.y >= 0 && diagonalCopy > 0;
		coordsIncr = coordsIncr - BoardCoord{ .x = 1, .y = 1 }, diagonalCopy--) // Check for down-left
	{
		if (!CheckSquare(finalVector, pieceColor, coordsIncr.x, coordsIncr.y))
			break;
	}

	diagonalCopy = diagonal;
	for (BoardCoord coordsIncr = coords + BoardCoord{ .x = 1, .y = -1 };
		coordsIncr.x < size && coordsIncr.y >= 0 && diagonalCopy > 0;
		coordsIncr = coordsIncr + BoardCoord{ .x = 1, .y = -1 }, diagonalCopy--) // Check for down-right
	{
		if (!CheckSquare(finalVector, pieceColor, coordsIncr.x, coordsIncr.y))
			break;
	}

	return finalVector;
}

bool Board::CheckSquare(std::vector<sf::Vector2f>& finalVector, const Color pieceColor, const int8_t x, const int8_t y)
{
	if (x < 0 || x >= size || y < 0 || y >= size)
		return false;

	Piece* tempPiece = GetPieceAt(x, y);

	if (tempPiece != nullptr)
	{
		if (tempPiece->GetColor() == pieceColor)
		{
			//finalVector.push_back(BoardCoordToPos({ .x = x, .y = y })); // TODO: REMOVE THIS
			return false; // TODO: set to false after implementation is done
		}

		finalVector.push_back(BoardCoordToPos({ .x = x, .y = y }));
		return false;
	}

	finalVector.push_back(BoardCoordToPos({ .x = x, .y = y }));

	return true;

}

std::vector<sf::Vector2f> Board::PawnMovement(Piece& piece)
{
	std::vector<sf::Vector2f> finalVector;
	BoardCoord coords = piece.GetBoardPosition();
	Color pieceColor = piece.GetColor();
	Pawn& pawn = static_cast<Pawn&>(piece);

	int8_t vertical = 1;

	if (!pawn.HasMoved())
	{
		vertical++;
	}

	if (pieceColor == Color::White)
	{
		for (BoardCoord coordsIncr = coords + BoardCoord{ .x = 0, .y = 1 };
			coordsIncr.y < size && vertical > 0;
			coordsIncr = coordsIncr + BoardCoord{ .x = 0, .y = 1}, vertical--)	// Check for up
		{
			Piece* tempPiece = GetPieceAt(coordsIncr.x, coordsIncr.y);

			if (tempPiece == nullptr)
			{
				finalVector.push_back(BoardCoordToPos({ .x = coordsIncr.x, .y = coordsIncr.y }));
			}
		}

		BoardCoord coordsIncr = coords + BoardCoord{ .x = -1, .y = 1 };
		if (coordsIncr.x >= 0 && coordsIncr.y < size)							// Check for up-left
		{
			Piece* tempPiece = GetPieceAt(coordsIncr.x, coordsIncr.y);

			if (tempPiece != nullptr)
			{
				if (tempPiece->GetColor() != pieceColor)
				{
					finalVector.push_back(BoardCoordToPos({ .x = coordsIncr.x, .y = coordsIncr.y }));
				}
			}
		}

		coordsIncr = coords + BoardCoord{ .x = 1, .y = 1 };
		if (coordsIncr.x >= 0 && coordsIncr.y < size)							// Check for up-right
		{
			Piece* tempPiece = GetPieceAt(coordsIncr.x, coordsIncr.y);

			if (tempPiece != nullptr)
			{
				if (tempPiece->GetColor() != pieceColor)
				{
					finalVector.push_back(BoardCoordToPos({ .x = coordsIncr.x, .y = coordsIncr.y }));
				}
			}
		}
	}

	else
	{
		for (BoardCoord coordsIncr = coords + BoardCoord{ .x = 0, .y = -1 };
			coordsIncr.y >= 0 && vertical > 0;
			coordsIncr = coordsIncr - BoardCoord{ .x = 0, .y = 1 }, vertical--) // Check for down
		{
			Piece* tempPiece = GetPieceAt(coordsIncr.x, coordsIncr.y);

			if (tempPiece == nullptr)
			{
				finalVector.push_back(BoardCoordToPos({ .x = coordsIncr.x, .y = coordsIncr.y }));
			}
		}

		BoardCoord coordsIncr = coords - BoardCoord{ .x = 1, .y = 1 };
		if (coordsIncr.x >= 0 && coordsIncr.y >= 0)								// Check for down-left
		{
			Piece* tempPiece = GetPieceAt(coordsIncr.x, coordsIncr.y);

			if (tempPiece != nullptr)
			{
				if (tempPiece->GetColor() != pieceColor)
				{
					finalVector.push_back(BoardCoordToPos({ .x = coordsIncr.x, .y = coordsIncr.y }));
				}
			}
		}

		coordsIncr = coords + BoardCoord{ .x = 1, .y = -1 };
		if (coordsIncr.x < size && coordsIncr.y >= 0)							// Check for down-right
		{
			Piece* tempPiece = GetPieceAt(coordsIncr.x, coordsIncr.y);

			if (tempPiece != nullptr)
			{
				if (tempPiece->GetColor() != pieceColor)
				{
					finalVector.push_back(BoardCoordToPos({ .x = coordsIncr.x, .y = coordsIncr.y }));
				}
			}
		}
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
		if (newSelectedPiece)
		{
			pieceAvailableMoves = GetAvailableMovesPositions(*selectedPiece);
			newSelectedPiece = false;
		}

		for (const auto& move : pieceAvailableMoves)
		{
			spotSprite.setPosition(move.x, move.y);
			window.draw(spotSprite);
		}
	}
}

void Board::SelectClickedPiece(const sf::Vector2f& position)
{
	for (const auto& spotPosition : pieceAvailableMoves)
	{
		sf::Vector2f delta = spotPosition - position;
		delta.x = std::abs(delta.x);
		delta.y = std::abs(delta.y);

		if (delta.x < 50 && delta.y < 50)
		{
			MovePieceAt(*selectedPiece, PosToBoardCoord(spotPosition));
			selectedPiece->SetHasMoved(true);

			pieceAvailableMoves.clear();
			selectedPiece = nullptr;
			return;
		}
	}

	for (const auto& piece : pieces)
	{
		//TODO: if spot localbounds countains position, move piece to position

		if (piece->GetSprite().getGlobalBounds().contains(position))
		{
			newSelectedPiece = selectedPiece != piece.get();
			selectedPiece = piece.get();

			return;
		}
	}

	newSelectedPiece = true;
	selectedPiece = nullptr;
}

void Board::MovePieceAt(Piece& piece, const BoardCoord coords)
{
	BoardCoord previousCoords = piece.GetBoardPosition();
	grid[previousCoords.y][previousCoords.x].SetPieceOnSquare(nullptr);

	Piece* target = GetPieceAt(coords.x, coords.y);

	if (target != nullptr && target->GetColor() != piece.GetColor())
	{
		const auto it = std::ranges::find(pieces, target,
			[](const std::unique_ptr<Piece>& ptr) 
			{
				return ptr.get();
			});

		if (it != pieces.end()) 
		{
			pieces.erase(it);
		}
	}

	grid[coords.y][coords.x].SetPieceOnSquare(&piece);
	piece.SetBoardPosition(coords);
	piece.GetSprite().setPosition(BoardCoordToPos(coords));
	piece.SetHasMoved(true);
}

Piece*& Board::GetPieceAt(const int8_t x, const int8_t y)
{
	return grid[y][x].GetPiece();
}
