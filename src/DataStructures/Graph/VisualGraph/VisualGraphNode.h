class VisualGraphNode : public GraphNode
{
    public:
        VisualGraphNode()
        {

        }

        VisualGraphNode(
                int index,
                int outDegree,
                Color color,
                Vector2f position) : GraphNode(index, outDegree)
        {
            _position = position;
            _color = color;

            InitShape();
        }

        Color GetColor() { return _color; }
        Vector2f GetPosition() { return _position; }
        CircleShape GetShape() { return _shape; }

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