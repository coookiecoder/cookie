#pragma once

#include <matrix.hpp>

namespace cookie {
    template<class Type>
    class Matrix4D final : public Matrix<Type> {
        public:
            Matrix4D();
            Matrix4D(std::initializer_list<std::initializer_list<Type>> value_list);

            ~Matrix4D() override = default;
    };

    template <class Type>
    Matrix4D<Type>::Matrix4D() : Matrix<Type>(4, 4) {

    }

    template <class Type>
    Matrix4D<Type>::Matrix4D(std::initializer_list<std::initializer_list<Type>> value_list) : Matrix<Type>(value_list) {
        if (this->_row != 4  || this->_col != 4) {
            throw std::invalid_argument("Invalid matrix size");
        }
    }

}