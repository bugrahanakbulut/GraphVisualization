#include "../Arrays/Array.h"

template<typename T>
class MinHeap
{
    public:
        MinHeap();
        void Insert(T value);
        T ExtractMin();
        T GetMin();

    private:
        Array<T> * _heap;
        int GetParent(int index);
        int GetLeftChild(int index);
        int GetRightChild(int index);
        void TopDownHeapify(int index);
        void BottomUpHeapify(int index);
};

template<typename T>
MinHeap<T>::MinHeap()
{
    _heap = new Array<T>();
}

template<typename T>
void MinHeap<T>::Insert(T value)
{
    _heap->Insert(value);

    BottomUpHeapify(_heap->Size() - 1);
}

template<typename T>
T MinHeap<T>::ExtractMin()
{
    T val = _heap->ValueAt(0);
    _heap->RemoveAt(0);

    T leaf = _heap->ValueAt(_heap->Size() - 1);
    _heap->RemoveAt(_heap->Size() - 1);

    _heap->Insert(leaf, 0);

    TopDownHeapify(0);

    return val;
}

template<typename T>
T MinHeap<T>::GetMin()
{
    if (_heap->Size() == 0)
    {
        throw runtime_error("Heap is empty.");
    }

    return _heap->ValueAt(0);
}

template<typename T>
int MinHeap<T>::GetParent(int index)
{
    return _heap->ValueAt(index / 2);
}

template<typename T>
int MinHeap<T>::GetLeftChild(int index)
{
    return _heap->ValueAt(2 * index + 1);
}

template<typename T>
int MinHeap<T>::GetRightChild(int index)
{
    return _heap->ValueAt(2 * index + 2);
}

template<typename T>
void MinHeap<T>::TopDownHeapify(int index)
{
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;

    if (leftChild >= _heap->Size())
    {
        return;
    }

    int targetSwapIndex = -1;

    if (rightChild >= _heap->Size())
    {
        if (_heap->ValueAt(index) > _heap->ValueAt(leftChild))
        {
            targetSwapIndex = leftChild;
        }
    }
    else
    {
        int lessChild = (_heap->ValueAt(rightChild) < _heap->ValueAt(leftChild)) ? rightChild : leftChild;

        if (_heap->ValueAt(index) > _heap->ValueAt(lessChild))
        {
            targetSwapIndex = lessChild;
        }
    }

    if (targetSwapIndex == -1)
        return;

    int tmp = _heap->ValueAt(targetSwapIndex);
    _heap->Set(targetSwapIndex, _heap->ValueAt(index));
    _heap->Set(index, tmp);

    TopDownHeapify(targetSwapIndex);
}

template<typename T>
void MinHeap<T>::BottomUpHeapify(int index)
{
    if (index == 0)
        return;

    int parentIndex = (int)(index / 2);

    if (_heap->ValueAt(index) < _heap->ValueAt(parentIndex))
    {
        int tmp = _heap->ValueAt(parentIndex);
        _heap->Set(parentIndex, _heap->ValueAt(index));
        _heap->Set(index, tmp);
    }

    BottomUpHeapify(parentIndex);
}

