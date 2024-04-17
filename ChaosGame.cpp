// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // load font and return message if the font fails to load properly
    Font font;
    if (!font.loadFromFile("C:/Game Design/Fonts/ARCADECLASSIC.TTF")) {
        cout << "Error with font" << endl;
        return EXIT_FAILURE;
    }

    // output instructions for the user
    Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(20);
    instructions.setFillColor(Color::White);
    instructions.setPosition(10.f, 10.f);
    instructions.setString("Click on any three points to create your triangle");

    Text fourth_point;
    fourth_point.setFont(font);
    fourth_point.setCharacterSize(20);
    fourth_point.setFillColor(Color::White);
    fourth_point.setPosition(10.f, 550.f);
    fourth_point.setString("Click on any fourth point to begin the chaos");

    // how do i choose vertices at random and how do i manipulate them to get half the distance between vertex and current positon



    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        window.clear();

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Draw vertices
        for (int i = 0; i < vertices.size(); i++)
        {
            CircleShape vertexShape(5);
            vertexShape.setPosition(vertices[i]);
            vertexShape.setFillColor(Color::Blue);
            window.draw(vertexShape);
        }

        // Draw points
        for (int i = 0; i < points.size(); i++)
        {
            CircleShape pointShape(2);
            pointShape.setPosition(points[i]);
            pointShape.setFillColor(Color::Yellow);
            window.draw(pointShape);

            //game works up to this point where attempt to duplicate points is made
            // 
            // vertices.at(0) is for testing purposes to create a single duplicate point. should be a random vertex
            // 
            //points.push_back(Vector2f((vertices.at(0).x + points.at(i).x) / 2.0, (vertices.at(0).y + points.at(i).y) / 2.0));
            //pointShape.setPosition(points.back());
            //window.draw(pointShape);
        }
        if (points.size() > 0)
        //for (int i = 0; i < points.size(); i++) 
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            /// 
            float vert_x;
            float vert_y;
            float cp_x;
            float cp_y;
            float mid_x;
            float mid_y;
            int blah = 0;
            // using vertex(0) for testing and first point only. implement random vertex later
            // get a second point first, then add more points
            // vertices[rand() % 3].y????
            vert_x = vertices[blah].x;
            vert_y = vertices[blah].y;
            cp_x = points[blah].x;
            cp_y = points[blah ].y;
            mid_x = (vert_x + cp_x) / 2.0;
            mid_y = (vert_y + cp_y) / 2.0;

            points.push_back(Vector2f(mid_x, mid_y));
            CircleShape pointShape(2);
            pointShape.setPosition(points[blah+1]);
            pointShape.setFillColor(Color::Yellow);
            window.draw(pointShape);


        }

        window.draw(instructions);
        window.draw(fourth_point);
        window.display();
    }

    return 0;
}
