class VisualGraphEdge : public GraphEdge<VisualGraphNode>
{
public:
    VisualGraphEdge()
    {

    }

    VisualGraphEdge(
            VisualGraphNode * sourceNode,
            VisualGraphNode * targetNode,
            Color edgeColor,
            int weight = 1) : GraphEdge<VisualGraphNode>(sourceNode, targetNode, weight)
    {
        _line = (Vertex *) calloc(sizeof(Vertex), 2);

        _edgeColor = edgeColor;

        _line[0] = Vertex(_sourceNode->GetPosition(), _edgeColor);
        _line[1] = Vertex(_targetNode->GetPosition(), _edgeColor);

        InitArrow();
    }

    Vertex * GetLine()
    {
        _line[0] = Vertex(_sourceNode->GetPosition(), _edgeColor);
        _line[1] = Vertex(_targetNode->GetPosition(), _edgeColor);

        return _line;
    }

    ConvexShape GetArrow()
    {
        InitArrow();

        return _directionArrow;
    }

    void SetColor (Color c)
    {
        _edgeColor = c;

        InitArrow();
    }

private:
    Vertex * _line;
    Color _edgeColor;
    float _arrowLen = 15;
    ConvexShape _directionArrow;

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
        _directionArrow.setFillColor(_edgeColor);
    }

};