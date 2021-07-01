#include "../LinkedList/LinkedList.h"
#include <iostream>

using namespace std;

template<typename T>
class Queue
{
    public:
        Queue()
        {
            _list = new LinkedList<T>();
        }

        T Front();
        void Enqueue(T value);
        T Dequeue();
        void PrintQueue();
        bool IsEmpty() { return _list->IsEmpty(); }


    private:
        LinkedList<T> * _list;

};

template<typename T>
T Queue<T>::Front()
{
    return _list->Front();
}

template<typename T>
void Queue<T>::Enqueue(T value)
{
    _list->PushBack(value);
}

template<typename T>
T Queue<T>::Dequeue()
{
    return _list->PopFront();
}

template<typename T>
void Queue<T>::PrintQueue()
{
    cout << "Queue Size : " << _list->Size() << " \n";

    cout << "Front Element : " << _list->Front() << " \n";

    cout << "Last Element : " << _list->Back() << " \n";

    _list->PrintList();

    cout << "--------------------------------------------\n";
}

