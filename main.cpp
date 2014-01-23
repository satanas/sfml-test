#include <SFML/Graphics.hpp>

int main(int, char const**) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "My First SFML example", sf::Style::Default, settings);
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        // error
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello World!");
    text.setCharacterSize(24);
    text.setColor(sf::Color::White);

    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(50, 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(text);
        window.draw(shape);

        window.display();
    }

    return 0;
}
