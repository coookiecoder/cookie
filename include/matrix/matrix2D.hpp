#pragma once

#include <matrix.hpp>

namespace cookie {
    template<class Type>
    class Matrix2D final : public Matrix<Type> {
        public:
            Matrix2D();
            Matrix2D(std::initializer_list<std::initializer_list<Type>> value_list);
            explicit Matrix2D(const Matrix<Type>& other);

            Matrix2D& operator=(const Matrix2D& other);

            ~Matrix2D() override = default;
    };

    template <class Type>
    Matrix2D<Type>::Matrix2D() : Matrix<Type>(2, 2) {

    }

    template <class Type>
    Matrix2D<Type>::Matrix2D(const Matrix<Type>& other) : Matrix<Type>(other) {
        if (this->_col != 2 || this->_row != 2) {
            throw std::invalid_argument("Invalid matrix size");
        }
    }

    template <class Type>
    Matrix2D<Type>& Matrix2D<Type>::operator=(const Matrix2D& other) {
        Matrix<Type>::operator=(other);

        return *this;
    }


    template <class Type>
    Matrix2D<Type>::Matrix2D(std::initializer_list<std::initializer_list<Type>> value_list) : Matrix<Type>(value_list) {
        if (this->_row != 2 || this->_col != 2) {
            throw std::invalid_argument("Invalid matrix size");
        }
    }

}