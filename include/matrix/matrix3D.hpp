#pragma once

#include <matrix.hpp>

namespace cookie {
    template<class Type>
    class Matrix3D final : public Matrix<Type> {
        public:
            Matrix3D();
            Matrix3D(std::initializer_list<std::initializer_list<Type>> value_list);
            explicit Matrix3D(const Matrix<Type>& other);

            Matrix3D& operator=(const Matrix<Type>& other);

            ~Matrix3D() override = default;
    };

    template <class Type>
    Matrix3D<Type>::Matrix3D() : Matrix<Type>(3, 3) {

    }

    template <class Type>
    Matrix3D<Type>::Matrix3D(const Matrix<Type>& other) : Matrix<Type>(other) {
        if (this->_col != 3 || this->_row != 3) {
            throw std::invalid_argument("Invalid matrix size");
        }
    }

    template <class Type>
    Matrix3D<Type>& Matrix3D<Type>::operator=(const Matrix<Type>& other) {
        if (&other == this)
            return *this;

        if (other.row() != 3 || other.col() != 3) {
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
    Matrix3D<Type>::Matrix3D(std::initializer_list<std::initializer_list<Type>> value_list) : Matrix<Type>(value_list) {
        if (this->_row != 3 || this->_col != 3)
            throw std::invalid_argument("Invalid matrix size");
    }
}