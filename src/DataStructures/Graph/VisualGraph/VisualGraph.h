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

    private:
        Color * _visualColorPalette;

        void InitColorPalette();
};

VisualGraph::VisualGraph(int nodeCount, int windowWidth, int windowHeight)
{
    _nodeCount = nodeCount;

    InitColorPalette();

    _nodes = (VisualGraphNode *) calloc(sizeof(VisualGraphNode), nodeCount);

    _adjLinkList = (LinkedList<VisualGraphEdge> *) calloc(sizeof(LinkedList<VisualGraphEdge>), nodeCount);

    for (int i = 0; i < nodeCount; i++)
    {
        _nodes[i] = VisualGraphNode(i, 0, Constants::GET_NODE_COLOR(), Utils::GetRandomVector2(windowWidth, windowHeight));

        _adjLinkList[i] = LinkedList<VisualGraphEdge>();
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

                VisualGraphEdge edge(
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
    /*LinkedList<int> * nodeStack  = new LinkedList<int>;

    bool isVisited[_nodeCount];
    int parents[_nodeCount];
    int levels[_nodeCount];

    for (int i = 0; i < _nodeCount; i++)
    {
        isVisited[i] = false;
        parents[i] = 0;
        levels[i] = 0;
    }

    levels[0] = 0;
    parents[0] = -1;
    nodeStack->PushFront(0);

    while (!nodeStack->IsEmpty())
    {
        int index = nodeStack->PopFront();

        isVisited[index] = true;

        if (parents[index] != -1)
            levels[index] = levels[parents[index]] + 1;

        _nodes[index].SetColor(_visualColorPalette[levels[index]]);

        // cout << "Node Id :" << index << " Level :" << levels[index] << "\n";

        for (int i = 0; i < _adjLinkList[index].Size(); i++)
        {
            int targetNode = _adjLinkList[index].ValueAt(i).GetTargetNode().GetIndex();

            if (!isVisited[targetNode])
            {
                parents[targetNode] = index;

                nodeStack->PushFront(targetNode);
            }
        }
    }*/

    Sleep(500);

    LinkedList<VisualGraphEdge> traversalOrder = DFS();

    for (int i = 0; i < traversalOrder.Size(); i++)
    {
        int source = traversalOrder.ValueAt(i).GetSourceNode().GetIndex();
        int target = traversalOrder.ValueAt(i).GetTargetNode().GetIndex();


        for (int i = 0; i < _nodes[source].GetOutDegree(); i++)
        {
            if (_adjLinkList[source].ValueAt(i).GetTargetNode().GetIndex() == target)
            {
                // _adjLinkList[source].ValueAt(i).GetSourceNode().SetColor(Color::Red);

                _nodes[source].SetColor(Color::Red);
                _nodes[target].SetColor(Color::Red);

                cout << source << " -- " << target << " ";
            }
        }

        Sleep(500);
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