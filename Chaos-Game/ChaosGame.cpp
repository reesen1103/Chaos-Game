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
    if (!font.loadFromFile("ARCADECLASSIC.TTF")) {
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
    fourth_point.setPosition(10.f, 40.f);
    fourth_point.setString("Click on any fourth point to begin the chaos");
    
    //output a completion message upon end of the simulation (see below)
    Text completion;
    completion.setFont(font);
    completion.setCharacterSize(20);
    completion.setFillColor(Color::White);
    completion.setPosition(10.f, 60.f);
    completion.setString("Simulation complete");

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
            CircleShape pointShape(1);
            pointShape.setPosition(points[i]);
            pointShape.setFillColor(Color::Yellow);
            window.draw(pointShape);

        }
        /// create points (limit of 5000 points for time and mercy on my CPU)
        /// process of creating fractal is done in four steps
        /// 1- randomly select a vertex
        /// 2- move half the distance from current position to selected vertex
        /// 3- plot and update current postion (will be last point in points vector)
        /// 4- repeat
        if (points.size() > 0 && points.size() < 5001)
        {
            // Choose a random vertex
            int rand_vertex = rand() % vertices.size();
            // Calculate midpoint between the random vertex and the last point in the points vector
            float mid_x = (vertices[rand_vertex].x + points.back().x) / 2.0;
            float mid_y = (vertices[rand_vertex].y + points.back().y) / 2.0;
            // Push back the newly generated coordinate
            points.push_back(Vector2f(mid_x, mid_y));
            // Draw the newly generated point
            CircleShape pointShape(1);
            pointShape.setPosition(Vector2f(mid_x, mid_y));
            pointShape.setFillColor(Color::Yellow);
            window.draw(pointShape);
        }
        if (points.size() == 5001) {
            window.draw(completion);
        }

        
        window.draw(instructions);
        window.draw(fourth_point);
        window.display();
    }

    return 0;
}
