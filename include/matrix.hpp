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
        Matrix(const Matrix<Type> &other);
        Matrix(Matrix<Type> &&other) noexcept ;

        Matrix(unsigned long row, unsigned long col);
        Matrix(std::initializer_list<std::initializer_list<Type>> value_list);

        Matrix<Type> &operator=(const Matrix<Type> &other);
        Matrix<Type> &operator=(Matrix<Type> &&other) noexcept ;

        [[nodiscard]] unsigned long row() const;
        [[nodiscard]] unsigned long col() const;

        Type* operator[](unsigned long row) const;

        Matrix<Type> transpose() const;

        virtual ~Matrix();
    };
}

namespace cookie {
    template <class Type>
    Matrix<Type> transpose(const Matrix<Type>& matrix) {
        Matrix<Type> result(matrix.col(), matrix.row());

        for (int row = 0; row < matrix.row(); ++row) {
            for (int col = 0; col < matrix.col(); ++col) {
                result[row][col] = matrix[col][row];
            }
        }

        return result;
    }
}

namespace cookie {
    template <class Type>
    Matrix<Type>::Matrix(const Matrix<Type>& other) : Matrix(other.row(), other.col()) {
        for (int row = 0; row < other.row(); ++row) {
            for (int col = 0; col < other.col(); ++col) {
                this->_data[row][col] = other._data[row][col];
            }
        }
    }

    template <class Type>
    Matrix<Type>::Matrix(Matrix<Type>&& other)  noexcept {
        this->_data = other._data;
        this->_row = other._row;
        this->_col = other._col;

        other._data = nullptr;
        other._row = 0;
        other._col = 0;
    }


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
    Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& other) {
        if (&other == this)
            return *this;

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
    Matrix<Type>& Matrix<Type>::operator=(Matrix<Type>&& other) noexcept {
        this->_data = other._data;
        this->_row = other._row;
        this->_col = other._col;

        other._data = nullptr;
        other._row = 0;
        other._col = 0;

        return *this;
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
    Type* Matrix<Type>::operator[](unsigned long row) const {
        return this->_data[row];
    }

    template <class Type>
    Matrix<Type> Matrix<Type>::transpose() const {
        Matrix<Type> result = cookie::transpose(*this);

        return result;
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
        if (matrix.col() == 0 || matrix.row() == 0) {
            os << "Matrix empty";
            return os;
        }

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