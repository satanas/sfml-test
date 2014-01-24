#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#define MAX_FRAME_SAMPLES 30
#define MAX_SPRITES 1000
static const float SCALE = 30.0f;

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

void createGround(b2World& world, float x, float y) {
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(x, y);
    bodyDef.type = b2_staticBody;
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(33.f, -1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}

void createBox(b2World& world, int mouseX, int mouseY) {
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(mouseX/SCALE, mouseY/SCALE);
    bodyDef.type = b2_dynamicBody;
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(30.0f/SCALE, 30.0f/SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.7f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
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

    // Box2D
    b2Vec2 gravity(0.0f, 10.0f);
    b2World world(gravity);

    createGround(world, 0.0f, 20.0f);

    /** Prepare textures */
    sf::Texture GroundTexture;
    sf::Texture BoxTexture;
    GroundTexture.loadFromFile("ground.png");
    BoxTexture.loadFromFile("box.png");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

    //    window.clear(sf::Color::Black);

    //    sprintf(buff, "FPS: %3.2f", framesPerSecond(clock));
    //    fps.setString(sf::String(buff));


    //    //for (int i=0; i<MAX_SPRITES; i++) {
    //    //    sf::Sprite s = sprites[i];
    //    //    s.setScale(rand() % 2 + 1, 2);
    //    //    s.setRotation((rand() % 720) - 360);
    //    //    window.draw(s);
    //    //}

    //    window.draw(text);
    //    window.draw(fps);

    //    window.display();
    //}


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int MouseX = sf::Mouse::getPosition(window).x;
            int MouseY = sf::Mouse::getPosition(window).y;
            createBox(world, MouseX, MouseY);
        }
        world.Step(1.0f/60.f, 8, 3);

        window.clear(sf::Color::White);
        int BodyCount = 0;
        for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext()) {
            if (BodyIterator->GetType() == b2_dynamicBody) {
                sf::Sprite Sprite;
                Sprite.setTexture(BoxTexture);
                Sprite.setOrigin(0.5f * SCALE, 0.5f * SCALE);
                Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                window.draw(Sprite);
                ++BodyCount;
            } else {
                sf::Sprite GroundSprite;
                GroundSprite.setTexture(GroundTexture);
                GroundSprite.setOrigin(15.0f * SCALE, 0.5f * SCALE);
                GroundSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
                GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                window.draw(GroundSprite);
            }
        }
        window.display();
    }

    return 0;
}


//#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
//
///** We need this to easily convert between pixel and real-world coordinates*/
//static const float SCALE = 30.f;
//
///** Create the base for the boxes to land */
//void CreateGround(b2World& World, float X, float Y);
//
///** Create the boxes */
//void CreateBox(b2World& World, int MouseX, int MouseY);
//
//int main()
//{
//    /** Prepare the window */
//    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
//    Window.setFramerateLimit(60);
//
//    /** Prepare the world */
//    b2Vec2 Gravity(0.f, 9.8f);
//    b2World World(Gravity);
//    CreateGround(World, 400.f, 500.f);
//
//    /** Prepare textures */
//    sf::Texture GroundTexture;
//    sf::Texture BoxTexture;
//    GroundTexture.loadFromFile("ground.png");
//    BoxTexture.loadFromFile("box.png");
//
//    while (Window.isOpen())
//    {
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//        {
//            int MouseX = sf::Mouse::getPosition(Window).x;
//            int MouseY = sf::Mouse::getPosition(Window).y;
//            CreateBox(World, MouseX, MouseY);
//        }
//        World.Step(1/60.f, 8, 3);
//
//        Window.clear(sf::Color::White);
//        int BodyCount = 0;
//        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
//        {
//            if (BodyIterator->GetType() == b2_dynamicBody)
//            {
//                sf::Sprite Sprite;
//                Sprite.setTexture(BoxTexture);
//                Sprite.setOrigin(16.f, 16.f);
//                Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
//                Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
//                Window.draw(Sprite);
//                ++BodyCount;
//            }
//            else
//            {
//                sf::Sprite GroundSprite;
//                GroundSprite.setTexture(GroundTexture);
//                GroundSprite.setOrigin(400.f, 8.f);
//                GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
//                GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
//                Window.draw(GroundSprite);
//            }
//        }
//        Window.display();
//    }
//
//    return 0;
//}
//
//void CreateBox(b2World& World, int MouseX, int MouseY)
//{
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
//    BodyDef.type = b2_dynamicBody;
//    b2Body* Body = World.CreateBody(&BodyDef);
//
//    b2PolygonShape Shape;
//    Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 1.f;
//    FixtureDef.friction = 0.7f;
//    FixtureDef.shape = &Shape;
//    Body->CreateFixture(&FixtureDef);
//}
//
//void CreateGround(b2World& World, float X, float Y)
//{
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
//    BodyDef.type = b2_staticBody;
//    b2Body* Body = World.CreateBody(&BodyDef);
//
//    b2PolygonShape Shape;
//    Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    Body->CreateFixture(&FixtureDef);
//}
