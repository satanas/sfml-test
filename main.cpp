#include <SFML/Graphics.hpp>

int main(int, char const**) {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First SFML example");
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

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(text);

        window.display();
    }

    return 0;
}
