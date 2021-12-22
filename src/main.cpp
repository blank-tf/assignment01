/* WARNING I AM NOT TAKING THIS COLLEGE COURSE,
 * I AM SIMPLY WATCHING THE VIDEOS ONLINE
 */


////////////////////////////////////////////////
//
//  Assignment:      COMP4300 - Assignment 1
//  Professor:       David Churchill
//  Year / Term:     FALL_2021
//  File Name:       main.cpp
//
//  Student Name:    Griffin Thompson
//  Student User:    griffinthompson
//  Student Email:   [removed]
//  Student ID:      [removed]
//  Group Member(s): Griffin Thompson
//
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>


// Window W H
// Font F S R G B
//  - F is font file
//  - S is font size
//  - (R,G,B) self-explanatory
// Rectangle N X Y SX SY R G B W H
//  - N is name
//  - (X,Y) pos
//  - (SX,SY) speed vector
//  - (R,G,B) self-explanatory
//  - (W,H) width-height
// Circle N X Y SX SY R G B R
//  - N is name
//  - (X,Y) pos
//  - (SX,SY) speed vector
//  - (R,G,B) self-explanatory
//  - R is radius
struct MovingCircle
{
    std::string name;
    float x, y;
    float sx, sy;
    int r, g, b;
    float radius;
};

struct MovingRectangle
{
    std::string name;
    float x, y;
    float sx, sy;
    int r, g, b;
    float w, h;
};

struct Window { int w, h; };

struct Font
{
    std::string filepath;
    int size;
    int r, g, b;
};

enum CONFIG_TOKEN
{
    WINDOW,
    FONT,
    CIRCLE,
    RECTANGLE
};

void parse(std::ifstream& stream, std::vector<Window>& windowBucket, std::vector<Font>& fontBucket, std::vector<MovingCircle>& circleBucket, std::vector<MovingRectangle>& rectangleBucket)
{
    std::string word;
    CONFIG_TOKEN type;
    while (stream >> word)
    {
        if (word == "Window")
            type = WINDOW;
        else if (word == "Font")
            type = FONT;
        else if (word == "Rectangle")
            type = RECTANGLE;
        else if (word == "Circle")
            type = CIRCLE;

        switch (type)
        {
            case WINDOW: {
                Window window {};
                stream >> word;
std::cout << word << std::endl;
                window.w = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                window.h = std::stoi(word);

                windowBucket.push_back(window);
                break;
            }
            case FONT: {
                Font font{};
                stream >> word;
std::cout << word << std::endl;
                font.filepath = word;
                stream >> word;
std::cout << word << std::endl;
                font.size = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                font.r = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                font.g = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                font.b = std::stoi(word);

                fontBucket.push_back(font);
                break;
            }
            case CIRCLE: {
                MovingCircle circle {};
                stream >> word;
std::cout << word << std::endl;
                circle.name = word;
                stream >> word;
std::cout << word << std::endl;
                circle.x = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                circle.y = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                circle.sx = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                circle.sy = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                circle.r = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                circle.g = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                circle.b = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                circle.radius = std::stof(word);
                
                circleBucket.push_back(circle);
                break;
            }
            case RECTANGLE: {
                MovingRectangle rectangle {};
                stream >> word;
std::cout << word << std::endl;
                rectangle.name = word;
                stream >> word;
std::cout << word << std::endl;
                rectangle.x = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.y = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.sx = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.sy = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.r = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.g = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.b = std::stoi(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.w = std::stof(word);
                stream >> word;
std::cout << word << std::endl;
                rectangle.h = std::stof(word);
                break;
            }
        }
    }
}

int main() {
    std::vector<MovingRectangle> rectangleList;
    std::vector<MovingCircle> circleList;
    std::vector<Window> windowList;
    std::vector<Font> fontList;
    
    
    // open file
    std::ifstream file;
    file.open("config.txt", std::ios::in);

    parse(file, windowList, fontList, circleList, rectangleList);

    file.close();

    int wWidth = windowList[0].w;
    int wHeight = windowList[0].h;

    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");

    // let's make a shape that we will draw to the screen
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(300.0f, 300.0f);
    float circleMoveSpeed = -0.01f;

    // load font.
    sf::Font myFont;

    if (!myFont.loadFromFile(fontList[0].filepath))
    {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    sf::Text text("Sample Text", myFont, 24);

    // position the top-left corner of the text so that the text aligns on the bottom
    // text character size is in pixels, so move the text up from the bottom by its height
    text.setPosition(0, wHeight - (float)text.getCharacterSize());

    // main loop - continues for each frame while window is open
    while (window.isOpen())
    {
        // event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            // this event trigerrs when the window is closed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // this event is triggered when a key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed with code = " << event.key.code << std::endl;

                // example, what happens when x is pressed
                if (event.key.code == sf::Keyboard::X)
                {
                    // reverse circle direction
                    circleMoveSpeed *= -1.0f;
                }
            }
        }

        // basic animation - move the each frame if its still in frame
        circle.setPosition(circle.getPosition() + sf::Vector2f(circleMoveSpeed, circleMoveSpeed));

        // basic rendering function calls
        window.clear();
        window.draw(circle);
        window.draw(text);
        window.display();
    }

    return 0;
}
