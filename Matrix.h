//
//  Matrix.h
//  LinearnaAlgebra
//
//  Created by Ivan Krpelnik on 20/03/16.
//  Copyright © 2016 Ivan Krpelnik. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

#include <string>
#include <iostream>

namespace LinearnaAlgebra
{

typedef unsigned long UL;

struct Matrix_error {
    std::string msg;
    Matrix_error(const char *s) :msg(s) {};
    Matrix_error(std::string s) :msg(s) {};
};

inline void errorM(const char *s) { throw Matrix_error(s); }

template<class Type = double>
class Matrix {
public:
    Matrix(UL row, UL col) :row(row), col(col), elem(new Type[row*col]) {};

    Matrix(UL row, UL col, std::vector<Type> v) :row(row), col(col), elem(new Type[row*col]) {
        set(v);
    }

    Matrix(UL row, UL col, Type a[]) :row(row), col(col), elem(new Type[row*col]) {
        for(int i = 0; i < row*col; i++)
            elem[i] = a[i];
    }

    Matrix(const Matrix<Type>& other) : row(other.row), col(other.col), elem(new Type[other.row*other.col]) {
        for(int i = 0; i < row*col; i++)
            elem[i] = other.elem[i];
    }

    ~Matrix() {
        delete[] elem;
    }

    void set(std::vector<Type> v) {
        if(v.size() != row*col) errorM("set: sizes don't match");
        int i = 0;
        for(auto value : v) {
            elem[i++] = value;
        }
    }

    std::vector<Type> getElems() {
        return std::vector<Type>(elem, elem + row*col);
    }

    UL getR() const { return row; }
    UL getC() const { return col; }

    //x, y not included
    Matrix<Type> subMatrix(UL x, UL y) const {
        if(x > row || y > col) errorM("subMatrix index out of range");
        Matrix<Type> res(row-1, col-1);
        std::vector<int> vx, vy;
        for(int i = 0; i < row; i++) {
            if(i == x) continue;
            vx.push_back(i);
        }
        for(int j = 0; j < col; j++) {
            if(j == y) continue;
            vy.push_back(j);
        }
        for(int i = 0; i < row - 1; i++)
            for(int j = 0; j < col - 1; j++)
                res(i, j) = (*this)(vx[i], vy[j]);
        return res;
    }

    Type determinant() const {
        if(row != col) errorM("DET - not a square matrix");

        if(row == 1) return (*this)(0, 0);
        if(row == 2) return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);

        Type sum = 0;
        for(int i = 0; i < row; i++)
            sum += (i % 2 == 0 ? 1 : -1) * (*this)(0, i) * subMatrix(0, i).determinant();
        return sum;
    }

    Matrix<Type> cofactor() {
        Matrix res(row, col);
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++) {
                res(i, j) =
                    (i % 2 == 0 ? 1 : -1) *
                    (j % 2 == 0 ? 1 : -1) *
                    subMatrix(i, j).determinant();
            }
        return res;
    }

    Type& operator() (UL x, UL y) {
        if(x >= row || y >= col) errorM("index out of range");
        return this->elem[x*col+y];
    }

    Type operator() (UL x, UL y) const {
        if(x >= row || y >= col) errorM("index out of range");
        return this->elem[x*col+y];
    }

    //inverse
    Matrix<Type> operator~() {
        return !cofactor() / determinant();
    }

    //transpose
    Matrix<Type>& operator!=(const Matrix<Type> &other) {
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                (*this)(i, j) = other(j, i);
        return *this;
    }

    Matrix<Type> operator!() {
        return Matrix<Type>(col, row) != (*this);
    }

    Matrix<Type>& operator+=(const Matrix<Type> &other) {
        if(getR() != other.row || col != other.getC())
            errorM("+ Incompatible size");

        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                (*this)(i, j) += other(i, j);
        return *this;
    }

    Matrix<Type>& operator-=(const Matrix<Type> &other) {
        if(row != other.row || col != other.col)
            errorM("- Incompatible size");

        for(int i = 0; i < getR(); i++)
            for(int j = 0; j < getC(); j++)
                (*this)(i, j) -= other(i, j);
        return *this;
    }

    Matrix<Type>& operator*=(const Type& coeff) {
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                (*this)(i, j) *= coeff;
        return *this;
    }

    Matrix<Type>& operator/=(const Type& coeff) {
        return (*this) *= (1 / coeff);
    }

private:
    Type *elem;
    UL row, col;
};

template<class Type = double>
Matrix<Type> operator*(Matrix<Type> m1, Matrix<Type> m2) {
    if(m1.getC() != m2.getR()) errorM("* Incompatible size");
    Matrix<Type> res(m1.getR(), m2.getC());
    for(int i = 0; i < res.getR(); i++)
        for(int j = 0; j < res.getC(); j++) {
            res(i, j) = 0;
            for(int k = 0; k < m1.getC(); k++)
                res(i, j) += m1(i, k) * m2(k, j);
        }
    return res;
}

template<class Type = double>
Matrix<Type> operator+(Matrix<Type> m1, Matrix<Type> m2) {
    return m1 += m2;
}

template<class Type = double>
Matrix<Type> operator-(Matrix<Type> m1, Matrix<Type> m2) {
    return m1 -= m2;
}


template<class Type = double>
Matrix<Type> operator*(Matrix<Type> m1, Type coeff) {
    return m1 *= coeff;
}

template<class Type = double>
Matrix<Type> operator/(Matrix<Type> m1, Type coeff) {
    return m1 /= coeff;
}

template<class Type = double>
std::ostream & operator<<(std::ostream & stream, const Matrix<Type>& m) {
    for(int i = 0; i < m.getR(); i++) {
        stream << "[ ";
        for(int j = 0; j < m.getC(); j++) {
            stream << m(i, j) << " ";
        }
        stream << "]\n";
    }
    return stream;
}

}
#endif /* Matrix_h */
