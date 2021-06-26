#include <iostream>
#include <vector>

using namespace std;

class GraphEdge
{
    public:
        GraphEdge(int source, int target, float weight)
        {
            _sourceVertex = source;
            _targetVertex = target;
            _weight = weight;
        }

        GraphEdge(int source, int target)
        {
            _sourceVertex = source;
            _targetVertex = target;
            _weight = 1;
        }

        int GetSourceVertex()
        {
            return _sourceVertex;
        }

        int GetTargetVertex()
        {
            return _targetVertex;
        }

        int GetWeight()
        {
            return _weight;
        }

    private:
        int _sourceVertex;
        int _targetVertex;
        float _weight;
};

class Graph
{
    private:
        int _vertexCount;
        int * _outDegrees;
        GraphEdge** _adjacencyList;

    public:
        Graph(int vertexCount);

        void ToString();
};


