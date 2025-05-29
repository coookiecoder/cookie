#pragma once

#include <iomanip>
#include <iostream>

#ifndef MATRIX_SET_W
#define MATRIX_SET_W 5
#endif

namespace cookie {
    template<class Type>
    class Matrix {
        protected:
            Type **_data = nullptr;
            unsigned long _row = 0;
            unsigned long _col = 0;

        public:
            Matrix() = default;
            Matrix(unsigned long row, unsigned long col);
            Matrix(std::initializer_list<std::initializer_list<Type>> value_list);

            [[nodiscard]] unsigned long row() const;
            [[nodiscard]] unsigned long col() const;

            const Type* operator[](unsigned long row) const;

            virtual ~Matrix();
    };

    template <class Type>
    Matrix<Type>::Matrix(const unsigned long row, const unsigned long col) : _row(row), _col(col) {
        this->_data = new Type*[row];

        for (int new_row = 0; new_row < row; ++new_row) {
            this->_data[new_row] = new Type[col];

            for (int new_col = 0; new_col < col; ++new_col) {
                this->_data[new_row][new_col] = Type();
            }
        }
    }

    template <class Type>
    Matrix<Type>::Matrix(std::initializer_list<std::initializer_list<Type>> value_list) : _row(value_list.size()), _col(value_list.begin()->size()){
        for (auto matrix_row: value_list) {
            if (matrix_row.size() != _col) {
                throw std::invalid_argument("invalid matrix size");
            }
        }

        this->_data = new Type*[_row];

        unsigned long row = 0;
        for (const auto& row_list : value_list) {
            _data[row] = new Type[_col];

            unsigned long col = 0;
            for (const auto& item : row_list) {
                _data[row][col++] = item;
            }

            ++row;
        }
    }


    template <class Type>
    unsigned long Matrix<Type>::row() const {
        return _row;
    }

    template <class Type>
    unsigned long Matrix<Type>::col() const {
        return _col;
    }

    template <class Type>
    const Type* Matrix<Type>::operator[](unsigned long row) const {
        return this->_data[row];
    }

    template <class Type>
    Matrix<Type>::~Matrix() {
        for (int row = 0; row < _row; ++row) {
            delete[] _data[row];
        }

        delete[] _data;
    }

    template<class Type>
    std::ostream& operator<<(std::ostream& os, const Matrix<Type>& matrix) {
        for (int row = 0; row < matrix.row(); ++row) {
            for (int col = 0; col < matrix.col(); ++col) {
                os << "[" << std::setw(MATRIX_SET_W) << matrix[row][col] << "]";
            }

            if (row != matrix.row() - 1) {
                os << std::endl;
            }
        }

        return os;
    }
}

namespace cookie {

}

#include <matrix/matrix2D.hpp>
#include <matrix/matrix3D.hpp>
#include <matrix/matrix4D.hpp>