#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#define MAX_FRAME_SAMPLES 30
#define MAX_SPRITES 200

int frames_count = 0;
float fps = 0.0;

float framesPerSecond(sf::Clock & clock) {
    frames_count++;
    if (frames_count >= MAX_FRAME_SAMPLES) {
        fps = ((float)frames_count / (float)clock.getElapsedTime().asMilliseconds()) * 1000;
        clock.restart();
        frames_count = 0;
    }
    //if (clock.getElapsedTime().asMilliseconds() >= 1000) {
    //    clock.restart();
    //    fps = count;
    //    count = 0;
    //}
    fflush(stdout);
    return fps;
}

int main(int, char const**) {
    int width = 1000;
    int height = 600;
    char buff[15];

    srand(time(NULL));

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "My First SFML example", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello Benchmark!");
    text.setCharacterSize(24);
    int text_x = (width - (text.getCharacterSize() * 5)) / 2;
    text.setPosition(text_x, 0);
    text.setColor(sf::Color::White);

    sf::Text fps;
    fps.setFont(font);
    fps.setCharacterSize(20);
    fps.setColor(sf::Color::White);

    sf::Texture barrel;
    if (!barrel.loadFromFile("barrel.png")) {
        return EXIT_FAILURE;
    }

    std::vector<sf::Sprite> sprites(MAX_SPRITES);
    for (int i=0; i<MAX_SPRITES; i++) {
        sprites[i].setTexture(barrel);
        int x = rand() % width;
        int y = rand() % height;
        sprites[i].setPosition(x, y);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        sprintf(buff, "FPS: %3.2f", framesPerSecond(clock));
        fps.setString(sf::String(buff));


        for (int i=0; i<MAX_SPRITES; i++) {
            sf::Sprite s = sprites[i];
            s.setScale(rand() % 2 + 1, 2);
            s.setRotation((rand() % 720) - 360);
            window.draw(s);
        }

        window.draw(text);
        window.draw(fps);

        window.display();
    }

    return 0;
}
