#include <stdexcept>
#include <iostream>
#include "LinkedListNode.h"

using namespace std;

template<typename T>
class LinkedList   
{
    public:
        LinkedList()
        {
            _head = _tail = nullptr;
            _size = 0;
        }

        int Size();
        bool IsEmpty();
        T ValueAt(int index);
        void PushFront(T value);
        T PopFront();
        void PushBack(T value);
        T PopBack();
        T Front();
        T Back();
        void InsertAt(int index, T value);
        void Delete(T value);
        T DeleteAt(int index);
        void Reverse();
        void PrintList();
        void Clear();

    private:
        int _size;
        LinkedListNode<T> * _head;
        LinkedListNode<T> * _tail;

        LinkedListNode<T> * GetNode(int index);
};

template<typename T>
int LinkedList<T>::Size()
{
    return _size;
}

template<typename T>
bool LinkedList<T>::IsEmpty()
{
    return _size == 0;
}

template<typename T>
T LinkedList<T>::ValueAt(int index)
{
    if (index > _size)
    {
        throw runtime_error("Index out of linked list bounds.");
    }

    if (index < 0)
    {
        throw runtime_error("Index can not be smaller than 0.");
    }

    LinkedListNode<T> * tmp = _head;

    for (int i = 0; i < index; i++)
    {
        tmp = tmp->Next;
    }

    return tmp->Value;
}

template<typename T>
void LinkedList<T>::PushFront(T value)
{
    _head = new LinkedListNode<T>(value, _head);

    if (_tail == nullptr)
    {
        _tail = _head;
    }

    _size++;
}

template<typename T>
T LinkedList<T>::PopFront()
{
    if (_head == nullptr)
    {
        throw runtime_error("Head is null can not pop from front of list.");
    }

    T val = _head->Value;
    _head = _head->Next;
    _size--;

    return val;
}

template<typename T>
void LinkedList<T>::PushBack(T value)
{
    if (_head == nullptr)
    {
        _head = new LinkedListNode<T>(value, nullptr);

        _tail = _head;
    }
    else
    {
        _tail->InsertAfter(value);

        _tail = _tail->Next;
    }

    _size++;
}

template<typename T>
T LinkedList<T>::PopBack()
{
    if (_size == 0)
    {
        throw runtime_error("List is already empty.");
    }

    T returnValue = _tail->Value;

    if (_size > 1)
    {
        LinkedListNode<T> *newTail = GetNode(_size - 2);

        newTail->Next = nullptr;

        _tail = newTail;
    }
    else
    {
        _head = nullptr;
        _tail = nullptr;
    }


    _size--;

    return returnValue;
}

template<typename T>
T LinkedList<T>::Front()
{
    return _head->Value;
}

template<typename T>
T LinkedList<T>::Back()
{
    return _tail->Value;
}

template<typename T>
void LinkedList<T>::InsertAt(int index, T value)
{
    LinkedListNode<T> * node = nullptr;

    if (index == 0)
    {
        node = _head;
    }
    else
    {
        node = GetNode(index - 1);
    }

    node->Next = new LinkedListNode<T>(value, node->Next);

    _size++;
}

template<typename T>
void LinkedList<T>::Delete(T value)
{
    LinkedListNode<T> * tmp = _head;

    if (_head->Value == value)
    {
        _head = _head->Next;

        _size--;

        return;
    }

    while (tmp->Next != nullptr)
    {
        if (tmp->Next->Value == value)
        {
            tmp->Next = tmp->Next->Next;

            _size--;
        }

        tmp = tmp->Next;
    }
}

template<typename T>
T LinkedList<T>::DeleteAt(int index)
{
    T deletedNodeValue = ValueAt(index);

    if (index == 0)
    {
        _head = _head->Next;

        _size--;

        return deletedNodeValue;
    }

    LinkedListNode<T> * prevNodeFromDeletedNode = GetNode(index - 1);

    prevNodeFromDeletedNode->Next = prevNodeFromDeletedNode->Next->Next;

    _size--;

    return deletedNodeValue;
}

template<typename T>
void LinkedList<T>::Reverse()
{
    LinkedListNode<T> * prev = nullptr;
    LinkedListNode<T> * next = nullptr;
    LinkedListNode<T> * cur = _head;

    _head = _tail;
    _tail = cur;

    while (cur != nullptr)
    {
        next = cur->Next;
        cur->Next = prev;
        prev = cur;
        cur = next;
    }
}

template<typename T>
void LinkedList<T>::PrintList()
{
    LinkedListNode<T> * tmp = _head;

    while(tmp != nullptr)
    {
        cout << tmp->Value << " ";

        tmp = tmp->Next;
    }

    cout << "\n";

    cout << "List Size : " << _size << " \n";

    if (_head != nullptr)
        cout << "Head Value : " << _head->Value << " \n";

    if (_tail != nullptr)
        cout << "Tail Value : " << _tail->Value << " \n";
}


template<typename T>
LinkedListNode<T> * LinkedList<T>::GetNode(int index)
{
    if (index < 0 || index >= _size)
        return nullptr;

    LinkedListNode<T> * tmp = _head;

    for (int i = 0; i < index; i++)
    {
        tmp = tmp->Next;
    }

    return tmp;
}

template<typename T>
void LinkedList<T>::Clear()
{
    _size = 0;
    _head = _tail = nullptr;
}