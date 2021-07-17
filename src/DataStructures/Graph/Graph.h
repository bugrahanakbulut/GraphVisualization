#include <vector>
#include <iostream>

#include "../../Utils/Utils.h"
#include "../../Utils/Constants.h"
#include "../Queue/Queue.h"
#include "GraphNode.h"
#include "GraphEdge.h"

using namespace std;

template<class T1 = GraphNode, class T2 = GraphEdge<GraphNode>>
class Graph
{
    public:
        Graph(int nodeCount);

        Graph()
        {

        }

        T1 * GetNodes() { return _nodes; }

        int GetNodeCount() { return _nodeCount; }

        LinkedList<T2* > * GetAdjLinkList() { return _adjLinkList; }

        LinkedList<T2 *> DFS();

        LinkedList<T2 *> BFS();

        LinkedList<T2 *> ShortestPath(int source, int target);


    protected:
        int _nodeCount;

        T1 * _nodes;

        LinkedList<T2 *> * _adjLinkList;
};

template<class T1, class T2>
Graph<T1, T2>::Graph(int nodeCount)
{
    _nodeCount = nodeCount;
}

template<class T1, class T2>
LinkedList<T2 *> Graph<T1, T2>::DFS()
{
    int parents[_nodeCount];
    bool isVisited[_nodeCount];
    LinkedList<int> * nodeStack = new LinkedList<int>();
    LinkedList<T2 *> traversalOrder = LinkedList<T2 *>();

    parents[0] = -1;

    for (int i = 0; i < _nodeCount; i++)
    {
        nodeStack->PushFront(i);

        while (!nodeStack->IsEmpty())
        {
            int curIndex = nodeStack->PopFront();

            if (!isVisited[curIndex])
            {
                int parent = parents[curIndex];
                if (parent != -1)
                {
                    for (int k = 0; k < _nodes[parent].GetOutDegree(); k++)
                    {
                        if (_adjLinkList[parent].ValueAt(k)->GetTargetNode()->GetIndex() == curIndex)
                        {
                            traversalOrder.PushBack(_adjLinkList[parent].ValueAt(k));
                        }
                    }
                }

                isVisited[curIndex] = true;

                for (int j = 0; j < _nodes[curIndex].GetOutDegree(); j++)
                {
                    int targetIndex = _adjLinkList[curIndex].ValueAt(j)->GetTargetNode()->GetIndex();

                    parents[targetIndex] = curIndex;

                    nodeStack->PushFront(targetIndex);
                }
            }
        }
    }
    return traversalOrder;
}

template<class T1, class T2>
LinkedList<T2 *> Graph<T1, T2>::BFS()
{
    Queue<int> nodeQueue;

    LinkedList<T2 *> traverseOrder = LinkedList<T2 *>();

    bool isVisited[_nodeCount];

    for (int i = 0 ; i < _nodeCount; i++)
    {
        isVisited[i] = false;
    }

    isVisited[0] = true;

    nodeQueue.Enqueue(0);

    while (!nodeQueue.IsEmpty())
    {
        int curIndex = nodeQueue.Dequeue();

        for (int i = 0; i < _adjLinkList[curIndex].Size(); i++)
        {
            if (!isVisited[_adjLinkList[curIndex].ValueAt(i)->GetTargetNode()->GetIndex()])
            {
                isVisited[_adjLinkList[curIndex].ValueAt(i)->GetTargetNode()->GetIndex()] = true;

                nodeQueue.Enqueue(_adjLinkList[curIndex].ValueAt(i)->GetTargetNode()->GetIndex());

                traverseOrder.PushBack(_adjLinkList[curIndex].ValueAt(i));
            }
        }
    }

    return traverseOrder;
}

template<class T1, class T2>
LinkedList<T2 *> Graph<T1, T2>::ShortestPath(int source, int target)
{
    Queue<int> nodeQueue;

    bool isVisited[_nodeCount];
    int distances[_nodeCount];
    int parents[_nodeCount];

    for (int i = 0; i < _nodeCount; i++)
    {
        isVisited[i] = false;
        distances[i] = INT_MAX;
        parents[i] = -1;
    }

    isVisited[source] = true;
    distances[source] = 0;
    parents[source] = -1;

    nodeQueue.Enqueue(source);

    while (!nodeQueue.IsEmpty())
    {
        int curIndex = nodeQueue.Dequeue();

        isVisited[curIndex] = true;

        for (int i = 0; i < _adjLinkList[curIndex].Size(); i++)
        {
            int w = _adjLinkList[curIndex].ValueAt(i)->GetWeight();
            int targetIndex = _adjLinkList[curIndex].ValueAt(i)->GetTargetNode()->GetIndex();

            if (distances[targetIndex] > distances[curIndex] + w)
            {
                distances[targetIndex] = distances[curIndex] + w;
                parents[targetIndex] = curIndex;

                // cout << "Path Updated " << curIndex << " -> " << targetIndex << " Distance : " << distances[targetIndex] << "\n";
            }

            if (!isVisited[targetIndex])
            {
                nodeQueue.Enqueue(targetIndex);
            }
        }
    }

    LinkedList<T2 *> path;

    if (parents[target] == -1)
    {
        return path;
    }

    LinkedList<int> traverseOrder;

    int curParent = parents[target];
    traverseOrder.PushFront(target);
    traverseOrder.PushFront(curParent);

    while (curParent != -1)
    {
        curParent = parents[curParent];

        traverseOrder.PushFront(curParent);
    }

    for (int i = 0; i < traverseOrder.Size() - 1; i++)
    {
        int curNode = traverseOrder.ValueAt(i);

        int nextNode = traverseOrder.ValueAt(i + 1);

        for (int j = 0; j < _adjLinkList[curNode].Size(); j++)
        {
            if (_adjLinkList[curNode].ValueAt(j)->GetTargetNode()->GetIndex() == nextNode)
            {
                path.PushBack(_adjLinkList[curNode].ValueAt(j));

                cout << "Edge Added Path " << curNode << " -> " << nextNode << "\n";
            }
        }
    }

    return path;
}
