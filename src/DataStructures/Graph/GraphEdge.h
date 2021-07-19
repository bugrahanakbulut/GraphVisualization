template<class T = GraphNode>
class GraphEdge
{
    public:
        GraphEdge() { }

        GraphEdge(T * sourceNode, T * targetNode, int weight = 1)
        {
            _sourceNode = sourceNode;
            _targetNode = targetNode;
            _weight = weight;
        }

        T * GetSourceNode() { return _sourceNode; }
        T * GetTargetNode() { return _targetNode; }
        int GetWeight() { return _weight; }

        friend bool operator>(const GraphEdge<T> &c1, const GraphEdge<T> &c2)
        {
            return c1._weight > c2._weight;
        }

        friend bool operator<(const GraphEdge<T> &c1, const GraphEdge<T> &c2)
        {
            return c1._weight < c2._weight;
        }

    protected:
        T * _sourceNode;
        T * _targetNode;
        int _weight;
};
