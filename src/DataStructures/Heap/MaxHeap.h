#include "../Arrays/Array.h"

#include <iostream>

using namespace std;

class MaxHeap
{
    private:
        Array<int> * _arr;

    public:
        MaxHeap()
        {
            _arr = new Array<int>(0);
        }

        MaxHeap(int size)
        {
            _arr = new Array<int>(size);
        }

        void Insert(int value);
        void BottomUpHeapify(int index);
        void TopDownHeapify(int index);
        int GetMax();
        int GetSize();
        bool IsEmpty();
        int ExtractMax();
        void PrintHeap();
};

int MaxHeap::GetMax()
{
    return _arr->ValueAt(0);
}

int MaxHeap::GetSize()
{
    return _arr->Size();
}

bool MaxHeap::IsEmpty()
{
    return _arr->IsEmpty();
}

void MaxHeap::Insert(int value)
{
    if (_arr->Size() == 0)
    {
        _arr->Insert(value, 0);

        return;
    }

    _arr->Insert(value, _arr->Size());

    BottomUpHeapify(_arr->Size() - 1);
}

void MaxHeap::BottomUpHeapify(int index)
{
    if (index == 0)
        return;

    int parentIndex = (int)(index / 2);

    if (_arr->ValueAt(index) > _arr->ValueAt(parentIndex))
    {
        int tmp = _arr->ValueAt(parentIndex);
        _arr->Set(parentIndex, _arr->ValueAt(index));
        _arr->Set(index, tmp);
    }

    BottomUpHeapify(parentIndex);
}

void MaxHeap::TopDownHeapify(int index)
{
    int leftChild = index * 2;
    int rightChild = index * 2 + 1;

    if (leftChild >= _arr->Size())
    {
        return;
    }

    int targetSwapIndex = -1;

    if (rightChild >= _arr->Size())
    {
        if (_arr->ValueAt(index) < _arr->ValueAt(leftChild))
        {
            targetSwapIndex = leftChild;
        }
    }
    else
    {
        int greatChild = (_arr->ValueAt(rightChild) > _arr->ValueAt(leftChild)) ? rightChild : leftChild;

        if (_arr->ValueAt(index) < _arr->ValueAt(greatChild))
        {
            targetSwapIndex = greatChild;
        }
    }

    if (targetSwapIndex == -1)
        return;

    int tmp = _arr->ValueAt(targetSwapIndex);
    _arr->Set(targetSwapIndex, _arr->ValueAt(index));
    _arr->Set(index, tmp);

    TopDownHeapify(targetSwapIndex);
}

int MaxHeap::ExtractMax()
{
    int max = _arr->ValueAt(0);

    _arr->Set(0, _arr->ValueAt(_arr->Size() - 1));
    _arr->RemoveAt(_arr->Size() - 1);

    TopDownHeapify(0);

    return max;
}

void MaxHeap::PrintHeap()
{
    cout << "Heap Max Element : " << GetMax() << "\n";
    cout << "Heap Cur Size : " << GetSize() << "\n";
}

