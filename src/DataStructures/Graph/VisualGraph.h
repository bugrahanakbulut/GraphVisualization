#include <cmath>

class VisualGraphNode : public GraphNode
{
    public:
        VisualGraphNode() { }
        VisualGraphNode(
                int index,
                int outDegree,
                Color color,
                Vector2f position)
                    : GraphNode(index, outDegree)
        {
            _position = position;
            _color = color;

            InitShape();
        }

    public:
        CircleShape GetShape() { return _shape; }
        Vector2f GetPosition() { return _position; }

        Color GetColor() { return _color; }

        void SetColor (Color c)
        {
            _color = c;

            _shape.setFillColor(_color);
        }


        float GetDistance(VisualGraphNode other)
        {
            float xpy = pow(other.GetPosition().x - _position.x, 2) +
                            pow(other.GetPosition().y - _position.y, 2);

            return pow(xpy, 0.5);
        }

    private:
        Vector2f _position;
        CircleShape _shape;
        Color _color;

        void InitShape()
        {
            _shape.setRadius(Constants::NODE_RADIUS);
            _shape.setOrigin(Constants::NODE_RADIUS, Constants::NODE_RADIUS);
            _shape.setPosition(_position);
            _shape.setFillColor(_color);
        }
};

class VisualGraphEdge : public GraphEdge<VisualGraphNode>
{
    public:
        VisualGraphEdge() {  };
        VisualGraphEdge(
                VisualGraphNode * sourceNode,
                VisualGraphNode * targetNode,
                Color edgeColor,
                int weight = 1) :
            GraphEdge<VisualGraphNode>(sourceNode, targetNode, weight)
        {
            _line = (Vertex *) calloc(sizeof(Vertex), 2);

            _line[0] = Vertex(_sourceNode->GetPosition(), _sourceNode->GetColor());
            _line[1] = Vertex(_targetNode->GetPosition(), _targetNode->GetColor());

            InitArrow();
        }

        Vertex * GetLine()
        {
            _line[0] = Vertex(_sourceNode->GetPosition(), _sourceNode->GetColor());
            _line[1] = Vertex(_targetNode->GetPosition(), _targetNode->GetColor());

            return _line;
        }

        ConvexShape GetShape()
        {
            InitArrow();

            return _directionArrow;
        }

    private:
        Vertex * _line;
        ConvexShape _directionArrow;
        float _arrowLen = 15;

        void InitArrow()
        {
            _directionArrow.setPointCount(3);

            _directionArrow.setPoint(0, Vector2f(-_arrowLen / 2, 0));
            _directionArrow.setPoint(1, Vector2f(+_arrowLen / 2, 0));
            _directionArrow.setPoint(2, Vector2f(0, _arrowLen));
            _directionArrow.setOrigin(Vector2f(0, _arrowLen));
            Vector2f dir = _targetNode->GetPosition() - _sourceNode->GetPosition();

            _directionArrow.setPosition(Vector2f(_sourceNode->GetPosition().x + (dir.x * 0.95f), _sourceNode->GetPosition().y + (dir.y * 0.95f)));


            float angle = (atan2 (dir.y, dir.x) * 180 / 3.14) - 90;

            _directionArrow.setRotation(angle);
            _directionArrow.setFillColor(_targetNode->GetColor());
        }

};

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
    LinkedList<int> * nodeStack  = new LinkedList<int>;

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
    }

    /*for (int i = 0; i < _nodeCount; i++)
    {
        cout << "Node Id :" << i << " Level :" << levels[i] << " Parent : " << parents[i] << "\n";
    }*/
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