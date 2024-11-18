#include "application.hpp"

Application::Application(const std::string_view& name)
{
    window.create(sf::VideoMode::getDesktopMode(), name.data());
    window.setVerticalSyncEnabled(true);
}

void Application::Run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        game.DrawGameSprites(window);

        window.display();
    }
}