#include "SFML/Graphics.hpp"
#include "DataStructures/Graph/Graph.h"
#include "Utils/GraphVisualizer.h"

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode(1600, 900), "Graph Visualization");

    Event event;

    GraphVisualizer g(100, 800,  1500);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::Closed:
                {
                    window.close();
                    break;
                }
            }
        }

        window.clear();

        for (int i = 0; i < g.GetNodeCount(); i++)
        {
            CircleShape circle;
            circle.setRadius(5);
            circle.setPosition(Vector2f(g.GetVisualNodes()[i].GetX(), g.GetVisualNodes()[i].GetY()));
            circle.setFillColor(Color(255, 0, 0));

            window.draw(circle);

            for (int j = 0; j < g.GetOutDegrees()[i]; j++)
            {
                Vector2f source(g.GetVisualNodes()[i].GetX(), g.GetVisualNodes()[i].GetY());
                Vector2f destination(g.GetAdjacencyList()[i][j].GetX(), g.GetAdjacencyList()[i][j].GetY());

                Vertex line[] =
                {
                    Vertex(source),
                    Vertex(destination)
                };

                window.draw(line, 2, Lines);
            }
        }

        window.display();
    }
}
