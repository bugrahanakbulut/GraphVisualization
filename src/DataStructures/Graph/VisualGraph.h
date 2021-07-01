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
                VisualGraphNode sourceNode,
                VisualGraphNode targetNode,
                Color edgeColor,
                int weight = 1) :
            GraphEdge<VisualGraphNode>(sourceNode, targetNode, weight)
        {

            _edgeColor = (Color *) calloc (sizeof(Color), 1);
            _line = (Vertex *) calloc(sizeof(Vertex), 2);

            * _edgeColor = edgeColor;

            _line[0] = Vertex(_sourceNode.GetPosition(), * _edgeColor);
            _line[1] = Vertex(_targetNode.GetPosition(), * _edgeColor);
        }

        Vertex * GetLine() { return _line; }

        Color GetColor() { return * _edgeColor; }

        void SetColor(Color color)
        {
            * _edgeColor = color;

            _line[0] = Vertex(_sourceNode.GetPosition(), * _edgeColor);
            _line[1] = Vertex(_targetNode.GetPosition(), * _edgeColor);
        }

    private:
        Color * _edgeColor;
        Vertex * _line;

};

class VisualGraph : public Graph<VisualGraphNode, VisualGraphEdge>
{
    public:
        VisualGraph(int nodeCount, int windowWidth, int windowHeight);
};

VisualGraph::VisualGraph(int nodeCount, int windowWidth, int windowHeight)
{
    _nodeCount = nodeCount;

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
                        _nodes[i],
                        _nodes[j],
                        Constants::GET_EDGE_COLOR());

                _adjLinkList[i].PushBack(edge);

                cout << i << " --> " << j << "\n";
            }
        }
    }
}