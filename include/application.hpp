#pragma once
#include <SFML/Window.hpp>

#include "game.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Application
{
	sf::RenderWindow window;

	Game game;

public:

	Application(const std::string_view& name);
	Application(const Application& application) = delete;
	Application& operator=(const Application& application) = delete;
	Application& operator=(const Application&& application) = delete;
	Application(Application&& application) = delete;

	void Run();
};
