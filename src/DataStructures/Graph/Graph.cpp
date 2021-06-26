#include <stdlib.h>

#include "Graph.h"
#include "../../Utils/Utils.h"

void InitRandomAdjacencyList(int vertexCount, GraphEdge*** adjacencyList, int ** outdegrees)
{
    * adjacencyList = (GraphEdge**) calloc(sizeof (GraphEdge*), vertexCount);

    * outdegrees = (int *) calloc(sizeof (int), vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        (* adjacencyList)[i] = (GraphEdge *) calloc(sizeof(GraphEdge), 1);

        for (int j = 0; j < vertexCount; j++)
        {
            if (i == j)
            {
                continue;
            }

            float dice = Utils::GetRandomFloat();

            if (dice < 0.5)
            {
                (*outdegrees)[i] += 1;

                int curElementCount = (*outdegrees)[i];

                (*adjacencyList)[i] = (GraphEdge *) realloc((*adjacencyList)[i],
                                                            sizeof(GraphEdge) * (curElementCount + 1));

                (*adjacencyList)[i][curElementCount - 1] = GraphEdge(i, j, 1);
            }
        }
    }
}

Graph::Graph(int vertexCount)
{
    _vertexCount = vertexCount;

    InitRandomAdjacencyList(_vertexCount, &_adjacencyList, &_outDegrees);
}

void Graph::ToString()
{
    for (int i = 0; i < _vertexCount; i++)
    {
        for (int j = 0; j < _outDegrees[i]; j++)
        {
            cout << _adjacencyList[i][j].GetSourceVertex() << " -> " << _adjacencyList[i][j].GetTargetVertex() << "\n";
        }
    }
}


