class GraphNode
{
public:
    GraphNode()
    {

    }

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