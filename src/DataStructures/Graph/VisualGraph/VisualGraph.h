#include <cmath>
#include "VisualGraphNode.h"
#include "VisualGraphEdge.h"

#include <windows.h>
#include <pthread.h>

class VisualGraph : public Graph<VisualGraphNode, VisualGraphEdge>
{
    public:
        VisualGraph(int nodeCount, int windowWidth, int windowHeight);

        void VisualDFS();

        void VisualBFS();

        void VisualShortestPath(int source, int target);

        void VisualizeCyclicEdges();

        LinkedList<VisualGraphEdge> * VisualizedEdges;

    private:
        Color * _visualColorPalette;

        void InitColorPalette();
};

VisualGraph::VisualGraph(int nodeCount, int windowWidth, int windowHeight)
{
    VisualizedEdges = new LinkedList<VisualGraphEdge>;

    _nodeCount = nodeCount;

    InitColorPalette();

    _nodes = (VisualGraphNode *) calloc(sizeof(VisualGraphNode), nodeCount);

    _adjLinkList = (LinkedList<VisualGraphEdge *> *) calloc(sizeof(LinkedList<VisualGraphEdge *>), nodeCount);

    for (int i = 0; i < nodeCount; i++)
    {
        _nodes[i] = VisualGraphNode(i, 0, Constants::GET_NODE_COLOR(), Utils::GetRandomVector2(windowWidth, windowHeight));

        _adjLinkList[i] = LinkedList<VisualGraphEdge *>();
    }

    for (int i = 0; i < nodeCount; i++)
    {
        for (int j = 0; j < nodeCount; j ++)
        {
            if (i == j) { continue; }

            float distance = _nodes[i].GetDistance(_nodes[j]);
            float dice = Utils::GetRandomFloat();

            bool canThereBeEdge =
                    (distance < Constants::ADJACENCY_DISTANCE_THRESHOLD && dice < Constants::ADJACENCY_POSSIBLITY) ||
                    (dice < Constants::ADJACENCY_POSSIBLITY_AFTER_EXCEED_THRESHOLD);

            if (canThereBeEdge)
            {
                _nodes[i].SetOutDegree(_nodes[i].GetOutDegree() + 1);

                VisualGraphEdge * edge = new VisualGraphEdge(
                                            &_nodes[i],
                                            &_nodes[j],
                                            Constants::GET_EDGE_COLOR());

                _adjLinkList[i].PushBack(edge);

                cout << i << " --> " << j << "\n";
            }
        }
    }
}

void VisualGraph::VisualDFS()
{
    VisualizedEdges->Clear();

    Sleep(500);

    LinkedList<VisualGraphEdge *> traversalOrder = DFS();

    for (int i = 0; i < traversalOrder.Size(); i++)
    {
        traversalOrder.ValueAt(i)->SetColor(Color::Red);

        cout << "Source Node : " << traversalOrder.ValueAt(i)->GetSourceNode()->GetIndex() << " -> " <<
        "Target Node : " << traversalOrder.ValueAt(i)->GetTargetNode()->GetIndex() << "\n";

        VisualizedEdges->PushBack(*(traversalOrder.ValueAt(i)));

        Sleep(500);
    }
}

void VisualGraph::VisualBFS()
{
    VisualizedEdges->Clear();

    Sleep(500);

    LinkedList<VisualGraphEdge *> traversalOrder = BFS();

    for (int i = 0; i < traversalOrder.Size(); i++)
    {
        traversalOrder.ValueAt(i)->SetColor(Color::Red);

        cout << "Source Node : " << traversalOrder.ValueAt(i)->GetSourceNode()->GetIndex() << " ->" <<
         "Target Node : " << traversalOrder.ValueAt(i)->GetTargetNode()->GetIndex() << "\n";

        VisualizedEdges->PushBack(*(traversalOrder.ValueAt(i)));

        Sleep(500);
    }
}

void VisualGraph::VisualShortestPath(int source, int target)
{
    LinkedList<VisualGraphEdge *> path = ShortestPath(source, target);

    VisualizedEdges->Clear();

    Sleep(1000);

    for (int i = 0; i < path.Size(); i++)
    {
        path.ValueAt(i)->SetColor(Color::Red);

        VisualizedEdges->PushBack(*(path.ValueAt(i)));

        Sleep(1000);
    }
}

void VisualGraph::VisualizeCyclicEdges()
{
    LinkedList<VisualGraphEdge *> cyclicEdges = DetermineCycles();

    Sleep(1000);

    for (int i = 0; i < cyclicEdges.Size(); i++)
    {
        cyclicEdges.ValueAt(i)->SetColor(Color::Red);

        VisualizedEdges->PushBack(*(cyclicEdges.ValueAt(i)));

        Sleep(1000);
    }
}

void VisualGraph::InitColorPalette()
{
    _visualColorPalette = (Color *) calloc(sizeof(Color), _nodeCount);

    for (int i = 0; i < _nodeCount; i ++)
    {
        float r = Utils::GetRandomFloat(0, 255);
        float g = Utils::GetRandomFloat(0, 255);
        float b = Utils::GetRandomFloat(0, 255);

        _visualColorPalette[i] = Color(r, g, b, 255);
    }
}


