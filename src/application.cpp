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

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                game.GetBoard().SelectClickedPiece(mousePosF);
            }

            if (event.type == sf::Event::Resized) 
            {
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear(sf::Color::Black);

        game.DrawGameSprites(window);

        window.display();
    }
}