#pragma once

#include <stdexcept>

namespace cookie {
    template <class Type, unsigned long size>
    class ArrayHeap {
        protected:
            Type *_data;

        public:
            ArrayHeap();

            Type& operator[](unsigned long index);

            ~ArrayHeap();
    };

    template <class Type, unsigned long size>
    class ArrayStack {
    protected:
        Type _data[size];

    public:
        ArrayStack() = default;

        Type& operator[](unsigned long index);

        ~ArrayStack() = default;
    };
}

namespace cookie {

}

namespace cookie {
    template <class Type, unsigned long size>
    ArrayHeap<Type, size>::ArrayHeap()
    {
        this->_data = new Type[size];
    }

    template <class Type, unsigned long size>
    Type& ArrayHeap<Type, size>::operator[](unsigned long index)
    {
        return this->_data[index];
    }

    template <class Type, unsigned long size>
    ArrayHeap<Type, size>::~ArrayHeap()
    {
        delete[] this->_data;
    }

    template <class Type, unsigned long size>
    Type& ArrayStack<Type, size>::operator[](unsigned long index)
    {
        return this->_data[index];
    }
}