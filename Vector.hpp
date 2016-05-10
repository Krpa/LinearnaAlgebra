//
//  Vector.hpp
//  LinearnaAlgebra
//
//  Created by Ivan Krpelnik on 17/03/16.
//  Copyright © 2016 Ivan Krpelnik. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <iostream>
#include <vector>
#include <cmath>
#include <string>


namespace LinearnaAlgebra {

struct Vector_error {
    std::string msg;
    Vector_error(const char *s) :msg(s) {}
    Vector_error(std::string s) :msg(s) {}
};

inline void errorV(const char *s) {
    throw Vector_error(s);
}

template<class Type = double>
class Vector {
    
public:
    Vector(unsigned long size);
    Vector(Vector<Type> const &other);
    Vector(Type v1, Type v2, Type v3);
    unsigned long size() const;
    double norm() const;
    Vector<Type>& flip();
    Vector<Type>& normalize();
    
    Vector<Type>& operator+=(const Vector<Type>& other);
    Vector<Type>& operator-=(const Vector<Type>& other);
    Vector<Type>& operator%=(const Vector<Type>& other);
    Vector<Type>& operator*=(const Type coeff);
    Vector<Type>& operator/=(const Type coeff);
    
    Type& operator()(int ind);
    Type operator()(int ind) const;
    
    template<class T>
    friend std::ostream & operator<<(std::ostream & stream, const Vector<T>& v);
    
    template<class T>
    friend Vector<T> flip(Vector<T>& v);
    
    template<class T>
    friend Vector<T> normalize(Vector<T>& v);
    
private:
    std::vector<Type> values;
};

template<class Type>
Vector<Type> operator+(Vector<Type> v1, Vector<Type> v2);

template<class Type>
Vector<Type> operator-(Vector<Type> v1, Vector<Type> v2);

template<class Type>
Vector<Type> operator%(Vector<Type> v1, Vector<Type> v2);

template<class Type>
Vector<Type> operator*(Vector<Type> v, const Type coeff);

template<class Type>
Type operator*(Vector<Type> v1, Vector<Type> v2);

template<class Type>
Vector<Type> operator/(Vector<Type> v, const Type coeff);

template<class Type>
double cosine(Vector<Type> v1, Vector<Type> v2);

template<class Type>
Vector<Type> nNormalize(Vector<Type> v);

template<class Type>
Vector<Type> nFlip(Vector<Type> v);

}
#endif /* Vector_hpp */
