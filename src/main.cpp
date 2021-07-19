#include <thread>

#include "Utils/Resources.h"
#include "DataStructures/Graph/Graph.h"
#include "DataStructures/Graph/VisualGraph/VisualGraph.h"

using namespace std;

void GraphThread(VisualGraph g)
{
    g.VisualDFS();
}

int main()
{
    Font font;

    font.loadFromFile("../Resources/Roboto.ttf");

    VisualGraph graph(10, 1500, 800);

    std::thread t (GraphThread, graph);

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
            for (int j = 0; j < graph.GetNodes()[i].GetOutDegree(); j++)
            {
                window.draw(graph.GetAdjLinkList()[i].ValueAt(j)->GetLine(), 2, Lines);

                window.draw(graph.GetAdjLinkList()[i].ValueAt(j)->GetArrow());
            }
        }

        for (int i = 0; i < graph.VisualizedEdges->Size(); i++)
        {
            window.draw(graph.VisualizedEdges->ValueAt(i).GetLine(), 2, Lines);

            window.draw(graph.VisualizedEdges->ValueAt(i).GetArrow());
        }

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

        window.display();
    }

}
