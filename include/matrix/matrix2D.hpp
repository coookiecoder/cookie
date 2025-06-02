#pragma once

#include <matrix.hpp>

namespace cookie {
    template<class Type>
    class Matrix2D final : public Matrix<Type> {
        public:
            Matrix2D();
            Matrix2D(std::initializer_list<std::initializer_list<Type>> value_list);
            explicit Matrix2D(const Matrix<Type>& other);

            Matrix2D<Type>& operator=(const Matrix<Type>& other);

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
    Matrix2D<Type>& Matrix2D<Type>::operator=(const Matrix<Type>& other) {
        if (&other == this)
            return *this;

        if (other.row() != 2 || other.col() != 2) {
            throw std::invalid_argument("Invalid matrix size");
        }

        if (this->_data) {
            for (int row = 0; row < this->_row; ++row) {
                delete[] this->_data[row];
            }
            delete[] this->_data;
        }

        this->_data = new Type*[other.row()];

        for (int new_row = 0; new_row < other.row(); ++new_row) {
            this->_data[new_row] = new Type[other.col()];

            for (int new_col = 0; new_col < other.col(); ++new_col) {
                this->_data[new_row][new_col] = other[new_row][new_col];
            }
        }

        return *this;
    }


    template <class Type>
    Matrix2D<Type>::Matrix2D(std::initializer_list<std::initializer_list<Type>> value_list) : Matrix<Type>(value_list) {
        if (this->_row != 2 || this->_col != 2) {
            throw std::invalid_argument("Invalid matrix size");
        }
    }

}