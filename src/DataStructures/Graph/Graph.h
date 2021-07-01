#include <vector>
#include <iostream>

#include "../../Utils/Utils.h"
#include "../../Utils/Constants.h"
#include "../Queue/Queue.h"
// #include "../LinkedList/LinkedList.h"


using namespace std;

class GraphNode
{
    public:
        GraphNode() { }

        GraphNode(int index, int outDegree)
        {
            _index = index;
            _outDegree = outDegree;
        }

        int GetIndex() { return _index; }

        int GetOutDegree() { return _outDegree; }
        void SetOutDegree(int val) { _outDegree = val; }

    protected :
        int _index;
        int _outDegree;
};

template<class T = GraphNode>
class GraphEdge
{
    public:
        GraphEdge() { }

        GraphEdge(T sourceNode, T targetNode, int weight = 1)
        {
            _sourceNode = sourceNode;
            _targetNode = targetNode;
            _weight = weight;
        }

        T GetSourceNode() { return _sourceNode; }
        T GetTargetNode() { return _targetNode; }
        int GetWeight() { return _weight; }

    protected:
        T _sourceNode;
        T _targetNode;
        int _weight;
};

template<class T1 = GraphNode, class T2 = GraphEdge<GraphNode>>
class Graph
{
    public:
        Graph() { }
        Graph(int nodeCount);

        int GetNodeCount() { return _nodeCount; }

        T1 * GetNodes() { return _nodes; }

        LinkedList<T2> * GetAdjLinkList() { return _adjLinkList; }

        bool DFS(int startingIndex, int targetIndex);

        bool BFS(int startingIndex, int targetIndex);


    protected:
        int _nodeCount;
        T1 * _nodes;

        LinkedList<T2> * _adjLinkList;
};

template<class T1, class T2>
Graph<T1, T2>::Graph(int nodeCount)
{
    /*_nodeCount = nodeCount;
    _nodes = (T1 *) calloc(sizeof(T1), nodeCount);
    _adjacencyList = (T2 **) calloc(sizeof(T2 *), nodeCount);

    // init adjacencyList randomly
    for (int i = 0; i < nodeCount; i++)
    {
        _nodes[i] = T1(i, 0);

        _adjacencyList[i] = (T2 *) calloc(sizeof(T2), 1);

        for (int j = 0; j < nodeCount; j++)
        {
            if (i == j) { continue; }

            float dice = Utils::GetRandomFloat();

            if (dice < Constants::DEFAULT_ADD_ADJACENCY)
            {
                _nodes[i].SetOutDegree(_nodes[i].GetOutDegree() + 1);

                _adjacencyList[i] = (T2 *) realloc(_adjacencyList[i], sizeof(T2) * _nodes[i].GetOutDegree());

                _adjacencyList[i][_nodes[i].GetOutDegree() - 1] = T2(_nodes[i], _nodes[j]);
            }
        }
    }*/
}

template<class T1, class T2>
bool Graph<T1, T2>::DFS(int startingIndex, int targetIndex)
{
    LinkedList<int> * nodeStack = new LinkedList<int>;

    LinkedList<T2> * traversedNodes = new LinkedList<T2>;

    bool isVisited[_nodeCount];

    for (int i = 0; i < _nodeCount; i++)
    {
        isVisited[i] = false;
    }

    nodeStack->PushFront(startingIndex);

    while (!nodeStack->IsEmpty())
    {
        int curIndex = nodeStack->ValueAt(0);

        nodeStack->DeleteAt(0);

        if (isVisited[curIndex])
        {
            continue;
        }

        isVisited[curIndex] = true;

        for (int i = 0; i < _nodes[curIndex].GetOutDegree(); i++)
        {
            _adjLinkList[curIndex].ValueAt(i).SetColor(Color::Green);

            int index = (_adjLinkList[curIndex]).ValueAt(i).GetTargetNode().GetIndex();

            traversedNodes->PushBack((_adjLinkList[curIndex]).ValueAt(i));

            if (index == targetIndex)
            {
                return true;
            }

            nodeStack->PushFront(index);
        }
    }
    return false;
}

template<class T1, class T2>
bool Graph<T1, T2>::BFS(int startingIndex, int targetIndex)
{
    Queue<int> nodeQueue;

    bool isVisited[_nodeCount];

    for (int i = 0 ; i < _nodeCount; i++)
    {
        isVisited[i] = false;
    }

    nodeQueue.Enqueue(startingIndex);

    while (!nodeQueue.IsEmpty())
    {
        int curIndex = nodeQueue.Dequeue();

        for (int i = 0; i < _adjLinkList[curIndex].Size(); i++)
        {
            if (!isVisited[_adjLinkList[curIndex].ValueAt(i).GetTargetNode().GetIndex()])
            {
                isVisited[_adjLinkList[curIndex].ValueAt(i).GetTargetNode().GetIndex()] = true;

                nodeQueue.Enqueue(_adjLinkList[curIndex].ValueAt(i).GetTargetNode().GetIndex());
            }
        }
    }

    return false;
}