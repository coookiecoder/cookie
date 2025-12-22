#pragma once

#include <matrix.hpp>

namespace cookie {
    template<class Type>
    class Matrix4D final : public Matrix<Type> {
        public:
            Matrix4D();
            Matrix4D(std::initializer_list<std::initializer_list<Type>> value_list);
            explicit Matrix4D(const Matrix<Type>& other);

            Matrix4D& operator=(const Matrix4D& other);

            ~Matrix4D() override = default;
    };

    template <class Type>
    Matrix4D<Type>::Matrix4D() : Matrix<Type>(4, 4) {

    }

    template <class Type>
    Matrix4D<Type>::Matrix4D(const Matrix<Type>& other) : Matrix<Type>(other) {
        if (this->_col != 4 || this->_row != 4) {
            throw std::invalid_argument("Invalid matrix size");
        }
    }

    template <class Type>
    Matrix4D<Type>& Matrix4D<Type>::operator=(const Matrix4D& other) {
        Matrix<Type>::operator=(other);

        return *this;
    }

    template <class Type>
    Matrix4D<Type>::Matrix4D(std::initializer_list<std::initializer_list<Type>> value_list) : Matrix<Type>(value_list) {
        if (this->_row != 4  || this->_col != 4) {
            throw std::invalid_argument("Invalid matrix size");
        }
    }

}