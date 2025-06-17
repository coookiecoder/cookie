#pragma once

#include <stdexcept>

namespace cookie {
    template <class Type, unsigned long size>
    class Array {
        protected:
            Type _data[size] = {};

        public:
            Array();

            Type& operator[](unsigned long index);

            ~Array();
    };
}

namespace cookie {

}

namespace cookie {
    template <class Type, unsigned long size>
    Array<Type, size>::Array() = default;

    template <class Type, unsigned long size>
    Type& Array<Type, size>::operator[](unsigned long index)
    {
        return this->_data[index];
    }

    template <class Type, unsigned long size>
    Array<Type, size>::~Array() = default;
}