//
//  Vector.cpp
//  LinearnaAlgebra
//
//  Created by Ivan Krpelnik on 17/03/16.
//  Copyright © 2016 Ivan Krpelnik. All rights reserved.
//

#include "Vector.h"

namespace LinearnaAlgebra {

template<class Type>
Vector<Type>::Vector(unsigned long size) {
    values.resize(size);
}

template<class Type>
Vector<Type>::Vector(Vector<Type> const &other) {
    for (auto v : other.values) {
        values.push_back(v);
    }
}

template<class Type>
Vector<Type>::Vector(Type v1, Type v2, Type v3) {
    values.push_back(v1);
    values.push_back(v2);
    values.push_back(v3);
}

template<class Type>
unsigned long Vector<Type>::size() const {
    return values.size();
}

template<class Type>
double Vector<Type>::norm() const {
    Type res = 0;
    for(Type v : values) {
        res += v*v;
    }
    return sqrt(res);
}

template<class Type>
Vector<Type>& Vector<Type>::flip() {
    for(auto &value : values) {
        value = -value;
    }
    return *this;
}

template<class Type>
Vector<Type>& Vector<Type>::normalize() {
    double n = norm();
    if(n == 0) errorV("norm = 0");
    return (*this) /= n;
}

template<class Type>
Vector<Type>& Vector<Type>::operator+=(const Vector<Type>& other) {
    if (this->size() != other.size()) errorV("+ Length error");
    for(int i = 0; i < values.size(); i++) {
        values[i] += other.values[i];
    }
    return *this;
}

template<class Type>
Vector<Type>& Vector<Type>::operator-=(const Vector<Type>& other) {
    if (this->size() != other.size()) errorV("- Length error");
    for(int i = 0; i < values.size(); i++) {
        values[i] -= other.values[i];
    }
    return *this;
}


template<class Type>
Vector<Type>& Vector<Type>::operator%=(const Vector<Type>& other) {
    if (this->size() != 3 && other.size() != 3) errorV("% length error");
    Type v1 = values[1] * other.values[2] - values[2] * other.values[1];
    Type v2 = values[2] * other.values[0] - values[0] * other.values[2];
    Type v3 = values[0] * other.values[1] - values[1] * other.values[0];
    values[0] = v1;
    values[1] = v2;
    values[2] = v3;
    return *this;
}

template<class Type>
Vector<Type>& Vector<Type>::operator*=(const Type coeff) {
    for(int i = 0; i < values.size(); i++) {
        values[i] *= coeff;
    }
    return *this;
}

template<class Type>
Vector<Type>& Vector<Type>::operator/=(const Type coeff) {
    for(int i = 0; i < values.size(); i++) {
        values[i] /= coeff;
    }
    return *this;
}

template<class Type>
Type& Vector<Type>::operator()(int ind) {
    return values[ind];
};

template<class Type>
Type Vector<Type>::operator()(int ind) const {
    return values[ind];
};

template<class Type>
Vector<Type> operator+(Vector<Type> v1, Vector<Type> v2) {
    return v1 += v2;
};

template<class Type>
Vector<Type> operator-(Vector<Type> v1, Vector<Type> v2) {
    return v1 -= v2;
};

template<class Type>
Vector<Type> operator%(Vector<Type> v1, Vector<Type> v2) {
    return v1 %= v2;
};

template<class Type>
Vector<Type> operator*(Vector<Type> v, const Type coeff) {
    return v *= coeff;
};

template<class Type>
Type operator*(Vector<Type> v1, Vector<Type> v2) {
    if (v1.size() != v2.size()) errorV("* Length error");
    Type sum = 0;
    for(int i = 0; i < v1.size(); i++) {
        sum += v1(i) *= v2(i);
    }
    return sum;
};

template<class Type>
Vector<Type> operator/(Vector<Type> v, const Type coeff) {
    return v /= coeff;
};

template<class Type>
double cosine(Vector<Type> v1, Vector<Type> v2) {
    double n1 = v1.norm(), n2 = v2.norm();
    if (n1 == 0 || n2 == 0) errorV("norm = 0");
    return v1 * v2 / (n1 * n2);
}

template<class T>
std::ostream &operator<<(std::ostream &stream, const Vector<T>&v) {
    stream << "[ ";
    for(auto value : v.values) {
        stream << value << " ";
    }
    stream << "]";
    return stream;
}

template<class Type>
Vector<Type> nNormalize(Vector<Type> v) {
    return v.normalize();
};

template<class Type>
Vector<Type> nFlip(Vector<Type> v) {
    return v.flip();
};

template class Vector<int>;
template Vector<int> operator+(Vector<int> v1, Vector<int> v2);
template Vector<int> operator-(Vector<int> v1, Vector<int> v2);
template Vector<int> operator%(Vector<int> v1, Vector<int> v2);
template Vector<int> operator*(Vector<int> v, const int coeff);
template int operator*(Vector<int> v1, Vector<int> v2);
template Vector<int> operator/(Vector<int> v, const int coeff);
template double cosine(Vector<int> v1, Vector<int> v2);
template std::ostream &operator<<(std::ostream &stream, const Vector<int>&v);
template Vector<int> nNormalize(Vector<int> v);
template Vector<int> nFlip(Vector<int> v);

template class Vector<double>;
template Vector<double> operator+(Vector<double> v1, Vector<double> v2);
template Vector<double> operator-(Vector<double> v1, Vector<double> v2);
template Vector<double> operator%(Vector<double> v1, Vector<double> v2);
template Vector<double> operator*(Vector<double> v, const double coeff);
template double operator*(Vector<double> v1, Vector<double> v2);
template Vector<double> operator/(Vector<double> v, const double coeff);
template double cosine(Vector<double> v1, Vector<double> v2);
template std::ostream &operator<<(std::ostream &stream, const Vector<double>&v);
template Vector<double> nNormalize(Vector<double> v);
template Vector<double> nFlip(Vector<double> v);

}
