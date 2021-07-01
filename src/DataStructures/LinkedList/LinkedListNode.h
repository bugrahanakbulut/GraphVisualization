template<typename T>
class LinkedListNode
{
    public:
        T Value;
        LinkedListNode<T> * Next;

        LinkedListNode() { };

        LinkedListNode(T value)
        {
            LinkedListNode(value, nullptr);
        }

        LinkedListNode(T value, LinkedListNode<T> * next)
        {
            Value = value;
            Next = next;
        }

        void InsertAfter(T value)
        {
            Next =  new LinkedListNode<T> (value, Next);
        }
};