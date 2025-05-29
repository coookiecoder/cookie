#pragma once

#include <matrix.hpp>

namespace cookie {
    template<class Type>
    class Matrix3D final : public Matrix<Type> {
        public:
            Matrix3D();
            Matrix3D(std::initializer_list<std::initializer_list<Type>> value_list);

            ~Matrix3D() override = default;
    };

    template <class Type>
    Matrix3D<Type>::Matrix3D() : Matrix<Type>(3, 3) {

    }

    template <class Type>
    Matrix3D<Type>::Matrix3D(std::initializer_list<std::initializer_list<Type>> value_list) : Matrix<Type>(value_list) {
        if (this->_row != 3 || this->_col != 3)
            throw std::invalid_argument("Invalid matrix size");
    }
}