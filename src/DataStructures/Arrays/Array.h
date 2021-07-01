//
// Custom Vector Implementation
//
template <class T>
class Array
{
    private:
        T* _elements;
        int _size;

    public:
        explicit Array<T>(int size)
        {
            if (size < 0)
            {
                throw std::runtime_error(" Size can not be negative.");
            }

            _size = size;

            _elements = new T[size];
        }

        ~Array()
        {
            if (_elements != nullptr) { delete _elements; }
        }

        int Size();

        bool IsEmpty();

        T At(int index);

        void Insert(T elem);

        void Insert(T elem, int index);

        T Remove(T elem);

        int FindItem(T elem);

        void Resize(int newCapacity);
};

template<typename T>
int Array<T>::Size()
{
    return _size;
}

template<typename T>
bool Array<T>::IsEmpty()
{
    return _size == 0;
}

template<typename T>
T Array<T>::At(int index)
{
    if (index < 0)
    {
        throw std::runtime_error("Index can not be negative.");
    }

    if (index >= Size())
    {
        throw std::runtime_error("Index out of array bounds.");
    }

    return _elements[index];
}

template<typename T>
void Array<T>::Insert(T elem)
{
    Resize(_size + 1);

    _elements[_size - 1] = elem;
}

template<typename T>
void Array<T>::Insert(T elem, int index)
{
    if (index < 0)
    {
        throw std::runtime_error("Index can not be negative.");
    }

    if (index >= Size())
    {
        throw std::runtime_error("Index out of array bounds.");
    }

    Resize(_size + 1);

    T tmp = _elements[index];
    _elements[index] = elem;

    for (int i = index; i < _size - 1; i ++)
    {
        T swapTmp = _elements[i + 1];

        _elements[i + 1] = tmp;

        tmp = swapTmp;
    }
}

template<typename T>
T Array<T>::Remove(T elem)
{
    int elemIndex = FindItem(elem);

    if (elemIndex < 0)
    {
        throw std::runtime_error("Array does not containing specified element.");
    }

    T deleted = _elements[elemIndex];

    for (int j = elemIndex; j < _size - 1; j++)
    {
        _elements[j] = _elements[j + 1];
    }

    Resize(Size() - 1);

    return deleted;
}

template<typename T>
int Array<T>::FindItem(T elem)
{
    for (int i = 0; i < _size; i++)
    {
        if (_elements[i] == elem)
        {
            return i;
        }
    }

    return -1;
}

template<typename T>
void Array<T>::Resize(int newCapacity)
{
    if (newCapacity < 0)
    {
        throw std::runtime_error(" Size can not be negative.");
    }

    _size = newCapacity;

    T* newList = new T[_size];

    for (int i = 0; i < _size; i++)
    {
        newList[i] = _elements[i];
    }

    delete _elements;

    _elements = newList;
}
