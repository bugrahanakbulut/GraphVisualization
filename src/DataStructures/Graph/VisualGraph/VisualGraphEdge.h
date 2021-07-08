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