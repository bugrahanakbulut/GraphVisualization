#include "Utils/Resources.h"

#include "DataStructures/Graph/Graph.h"
#include "DataStructures/Graph/VisualGraph.h"

// using namespace sf;
using namespace std;

int main()
{
    Font font;

    font.loadFromFile("../Resources/Roboto.ttf");

    VisualGraph graph(10, 1500, 800);

    graph.DFS(1, 0);

    RenderWindow window(VideoMode(1600, 900), "Graph Visualization");

    Event event;

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

        for (int i = 0; i < graph.GetNodeCount(); i++)
        {
            window.draw(graph.GetNodes()[i].GetShape());

            Text t;
            t.setFont(font);
            t.setCharacterSize(Constants::NODE_INDEX_CHAR_SIZE);
            t.setFillColor(Constants::GET_NODE_INDEX_TEXT_COLOR());
            t.setString(to_string(graph.GetNodes()[i].GetIndex()));
            t.setPosition(graph.GetNodes()[i].GetPosition());
            t.setOrigin(Constants::NODE_RADIUS, Constants::NODE_RADIUS);
            window.draw(t);
        }

        for (int i = 0; i < graph.GetNodeCount(); i++)
        {
            for (int j = 0; j < graph.GetNodes()[i].GetOutDegree(); j++)
            {
                window.draw(graph.GetAdjLinkList()[i].ValueAt(j).GetLine(), 2, Lines);
            }
        }

        window.display();
    }
}
