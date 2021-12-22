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

/* EXAMPLE config.txt ('*'s not included)
 *
 * Window 800 600
 * Font fonts/arial.ttf 18 255 255 255
 * Circle CGreen 100 100 -0.03 0.02 0 255 0 50
 * Circle CBlue 200 200 0.02 0.04 0 0 255 100
 * Circle CPurple 300 300 -0.02 -0.01 255 0 255 75
 * Rectangle RRed 200 200 0.1 0.15 255 0 0 50 25
 * Rectangle RGrey 300 250 -0.02 0.02 100 100 100 50 100
 * Rectangle RTeal 25 100 -0.02 -0.02 0 255 255 100 100
 *
*/


// Window W H
//  - W is width (duh)
//  - H is height (duh)
struct Window { int w, h; };

// Font F S R G B
//  - F is font file
//  - S is font size
//  - (R,G,B) self-explanatory
struct Font
{
    std::string filepath;
    int size;
    int r, g, b;
};

// Rectangle N X Y SX SY R G B W H
//  - N is name
//  - (X,Y) pos
//  - (SX,SY) speed vector
//  - (R,G,B) self-explanatory
//  - (W,H) width-height
struct Rectangle
{
    sf::RectangleShape rectangle = sf::RectangleShape();
    sf::Text text = sf::Text();

    std::string name;
    float x, y;
    float sx, sy;
    int r, g, b;
    float w, h;
};

// Circle N X Y SX SY R G B R
//  - N is name
//  - (X,Y) pos
//  - (SX,SY) speed vector
//  - (R,G,B) self-explanatory
//  - R is radius
struct Circle
{
    sf::CircleShape circle = sf::CircleShape();
    sf::Text text = sf::Text();

    std::string name;
    float x, y;
    float sx, sy;
    int r, g, b;
    float radius;
};

enum CONFIG_TOKEN
{
    WINDOW,
    FONT,
    CIRCLE,
    RECTANGLE
};

// parses the config file. Doesn't have error handling, i.e. if a word is misspelled
// or a circle has too few arguments things will blow up
void parse(std::ifstream& stream, std::vector<Window>& windowBucket, std::vector<Font>& fontBucket, std::vector<Circle>& circleBucket, std::vector<Rectangle>& rectangleBucket)
{
    std::string word;
    CONFIG_TOKEN type;
    // steps through the config file word by word
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

        // I know this is ugly, but it works, and, yeah, that's about it.
        switch (type)
        {
            case WINDOW: {
                Window window {};


                stream >> word;
                window.w = std::stoi(word);

                stream >> word;
                window.h = std::stoi(word);


                windowBucket.push_back(window);
                break;
            }
            case FONT: {
                Font font{};


                stream >> word;
                font.filepath = word;

                stream >> word;
                font.size = std::stoi(word);

                stream >> word;
                font.r = std::stoi(word);

                stream >> word;
                font.g = std::stoi(word);

                stream >> word;
                font.b = std::stoi(word);


                fontBucket.push_back(font);
                break;
            }
            case CIRCLE: {
                Circle circle {};


                stream >> word;
                circle.name = word;

                stream >> word;
                circle.x = std::stof(word);

                stream >> word;
                circle.y = std::stof(word);

                stream >> word;
                circle.sx = std::stof(word);

                stream >> word;
                circle.sy = std::stof(word);

                stream >> word;
                circle.r = std::stoi(word);

                stream >> word;
                circle.g = std::stoi(word);

                stream >> word;
                circle.b = std::stoi(word);

                stream >> word;
                circle.radius = std::stof(word);


                circleBucket.push_back(circle);
                break;
            }
            case RECTANGLE: {
                Rectangle rectangle {};


                stream >> word;
                rectangle.name = word;

                stream >> word;
                rectangle.x = std::stof(word);

                stream >> word;
                rectangle.y = std::stof(word);

                stream >> word;
                rectangle.sx = std::stof(word);

                stream >> word;
                rectangle.sy = std::stof(word);

                stream >> word;
                rectangle.r = std::stoi(word);

                stream >> word;
                rectangle.g = std::stoi(word);

                stream >> word;
                rectangle.b = std::stoi(word);

                stream >> word;
                rectangle.w = std::stof(word);

                stream >> word;
                rectangle.h = std::stof(word);


                rectangleBucket.push_back(rectangle);
                break;
            }
        }
    }
}

std::vector<Rectangle> rectangleList;
std::vector<Circle> circleList;
std::vector<Window> windowList;
std::vector<Font> fontList;

void draw(sf::RenderWindow& window)
{
    window.clear();


    // draw shapes with their names to the screen
    for (auto& i : circleList) {
        window.draw(i.circle);
        window.draw(i.text);
    }
    for (auto& i : rectangleList) {
        window.draw(i.rectangle);
        window.draw(i.text);
    }


    window.display();
    // this is just here because the shapes go too fast to read otherwise. remove if you want.
    sf::sleep(sf::microseconds(100));
}

void update(sf::RenderWindow& window)
{
    const float wWidth = (float)window.getSize().x;
    const float wHeight = (float)window.getSize().y;

    // update circle and circle's name text positions, then the same but for rectangles
    for (auto& i : circleList)
    {
        // first, we update the position of the circle
        auto old_position = i.circle.getPosition();
        i.circle.setPosition(old_position + sf::Vector2f(i.sx, i.sy));


        // now, we update the location of the shape's name text to the center of the shape.
        auto textBounds = i.text.getLocalBounds();
        auto textMiddleX = textBounds.width / 2.0f;
        auto textMiddleY = textBounds.height / 2.0f;
        auto circleLocalBounds = i.circle.getLocalBounds();
        auto middleOfCircle = sf::Vector2f(circleLocalBounds.width / 2, circleLocalBounds.height / 2);
        i.text.setPosition(i.circle.getPosition().x + middleOfCircle.x - textMiddleX, i.circle.getPosition().y + middleOfCircle.y - textMiddleY);


        // finally, we check the shape's global bounds against the bounds of the window to see if we need to bounce.
        auto circleGlobalBounds = i.circle.getGlobalBounds();
        // top and bottom
        if (circleGlobalBounds.top <0 || circleGlobalBounds.top + circleGlobalBounds.height > (float)wHeight)
        {
            i.sy *= -1.0f;
        }
        // left and right
        if (circleGlobalBounds.left <0 || circleGlobalBounds.left + circleGlobalBounds.width > (float)wWidth)
        {
            i.sx *= -1.0f;
        } 
    }

    for (auto& i : rectangleList)
    {
        // first, we update the position of the rectangle
        auto old_position = i.rectangle.getPosition();
        i.rectangle.setPosition(old_position + sf::Vector2f(i.sx, i.sy));


        // now, we update the location of the shape's name text to the center of the shape.
        auto textBounds = i.text.getLocalBounds();
        auto textMiddleX = textBounds.width / 2.0f;
        auto textMiddleY = textBounds.height / 2.0f;
        auto rectangleLocalBounds = i.rectangle.getLocalBounds();
        auto middleOfRectangle = sf::Vector2f(rectangleLocalBounds.width / 2, rectangleLocalBounds.height / 2);
        i.text.setPosition(i.rectangle.getPosition().x + middleOfRectangle.x - textMiddleX,
                           i.rectangle.getPosition().y + middleOfRectangle.y - textMiddleY);


        // finally, we check the shape's global bounds against the bounds of the window to see if we need to bounce.
        auto rectangleGlobalBounds = i.rectangle.getGlobalBounds();
        // top and bottom
        if (rectangleGlobalBounds.top < 0 || rectangleGlobalBounds.top + rectangleGlobalBounds.height > wHeight)
        {
            i.sy *= -1.0f;
        }
        // left and right
        if (rectangleGlobalBounds.left < 0 || rectangleGlobalBounds.left + rectangleGlobalBounds.width > wWidth)
        {
            i.sx *= -1.0f;
        }
    }
}

int main()
{
    // open file and parse
    std::ifstream file;
    file.open("config.txt", std::ios::in);
    parse(file, windowList, fontList, circleList, rectangleList);
    file.close();

    // initialize window
    int wWidth = windowList[0].w;
    int wHeight = windowList[0].h;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");

    // load font
    sf::Font font;
    if (!font.loadFromFile(fontList[0].filepath))
    {
        std::cerr << "Could not load font!\n";
        exit(-1);
    }

    // let's initialize all of our shapes and their according names.
    for (auto& i : circleList)
    {
        i.circle.setPosition(i.x, i.y);
        i.circle.setFillColor(sf::Color(i.r, i.g, i.b));
        i.circle.setRadius(i.radius);

        i.text.setString(i.name);
        i.text.setFont(font);
        i.text.setCharacterSize(fontList[0].size);
        i.text.setFillColor(sf::Color(fontList[0].r, fontList[0].g, fontList[0].b));
    }
    for (auto& i : rectangleList)
    {
        i.rectangle.setPosition(i.x, i.y);
        i.rectangle.setFillColor(sf::Color(i.r, i.g, i.b));
        i.rectangle.setSize(sf::Vector2f(i.w, i.h));

        i.text.setString(i.name);
        i.text.setFont(font);
        i.text.setCharacterSize(fontList[0].size);
        i.text.setFillColor(sf::Color(fontList[0].r, fontList[0].g, fontList[0].b));
    }


    // main loop - continues for each frame while window is open
    while (window.isOpen())
    {
        // event handling
        sf::Event event {};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        update(window);

        draw(window);
    }

    return 0;
}