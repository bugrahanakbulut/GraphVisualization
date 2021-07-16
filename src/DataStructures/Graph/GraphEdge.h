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

protected:
    T * _sourceNode;
    T * _targetNode;
    int _weight;
};
