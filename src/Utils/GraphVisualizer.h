#include <cmath>
#include "Utils.h"
#include "Constants.h"

using namespace std;

class GraphVisualNode
{
    public:
        GraphVisualNode(int x, int y)
        {
            _x = x;
            _y = y;
        }

        int GetX() { return _x; }
        int GetY() { return _y; }
        float GetDistance(GraphVisualNode other);

    private:
        int _x;
        int _y;
};

float GraphVisualNode::GetDistance(GraphVisualNode other)
{
    float xpy = pow(other.GetX() - _x, 2) + pow(other.GetY() - _y, 2);

    return pow(xpy, 0.5f);
}

class GraphVisualizer
{
    public:
        GraphVisualizer(int nodeCount, int windowHeight, int windowWidth);

        int GetNodeCount() { return _nodeCount; }
        int * GetOutDegrees() { return _outDegrees; }
        GraphVisualNode * GetVisualNodes() { return _nodes; }
        GraphVisualNode ** GetAdjacencyList() { return  _adjacencyList; }

    private:
        int _nodeCount;
        int * _outDegrees;
        GraphVisualNode * _nodes;
        GraphVisualNode ** _adjacencyList;
};

GraphVisualizer::GraphVisualizer(int nodeCount, int windowHeight, int windowWidth)
{
    _nodeCount = nodeCount;

    _nodes = (GraphVisualNode *) calloc(sizeof(GraphVisualNode), nodeCount);
    _adjacencyList = (GraphVisualNode **) calloc(sizeof(GraphVisualNode *), nodeCount);
    _outDegrees = (int *) calloc(sizeof (int), nodeCount);

    for (int i = 0; i < nodeCount; i++)
    {
        int x = (int) Utils::GetRandomFloat(0, windowWidth);
        int y = (int) Utils::GetRandomFloat(0, windowHeight);

        _nodes[i] = GraphVisualNode(x, y);
    }

    for (int i = 0; i < nodeCount; i ++)
    {
        _adjacencyList[i] = (GraphVisualNode *) calloc(sizeof(GraphVisualNode), 1);

        for (int j = 0; j < nodeCount; j++)
        {
            if (i == j)
            {
                continue;
            }

            float distance = _nodes[i].GetDistance(_nodes[j]);
            float dice = Utils::GetRandomFloat();

            bool canThereBeEdge =
                    (distance < Constants::ADJACENCY_DISTANCE_THRESHOLD && dice < Constants::ADJACENCY_POSSIBLITY) ||
                    (dice < Constants::ADJACENCY_POSSIBLITY_AFTER_EXCEED_THRESHOLD);

            if (canThereBeEdge)
            {
                _outDegrees[i]++;

                _adjacencyList[i] = (GraphVisualNode *) realloc(_adjacencyList[i], sizeof(GraphVisualNode) * (_outDegrees[i]) + 1);

                _adjacencyList[i][_outDegrees[i] - 1] = _nodes[j];
            }
        }
    }
}
