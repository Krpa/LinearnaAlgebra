//
//  main.cpp
//  LinearnaAlgebra
//
//  Created by Ivan Krpelnik on 17/03/16.
//  Copyright © 2016 Ivan Krpelnik. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace LinearnaAlgebra;

void prvi() {
    std::cout << "Prvi: " << "\n";
    Vector<> v1 = Vector<>(2, 3, -4) + Vector<>(-1, 4, -1);
    std::cout << v1 << "\n";

    int s = v1 * Vector<> (-1, 4, -1);
    std::cout << s << "\n";

    Vector<> v2 = v1 % Vector<>(2, 2, 4);
    std::cout << v2 << "\n";

    Vector<> v3 = nNormalize(v2);
    std::cout << v3 << "\n";

    Vector<> v4 = nFlip(v2);
    std::cout << v4 << "\n";

    int a1[9] = {1, 2, 3, 2, 1, 3, 4, 5, 1}, a2[9] = {-1, 2, -3, 5, -2, 7, -4, -1, 3};
    double b1[9] = {1, 2, 3, 2, 1, 3, 4, 5, 1}, b2[9] = {-1, 2, -3, 5, -2, 7, -4, -1, 3};

    Matrix<int> m1 = Matrix<int>(3, 3, a1) + Matrix<int>(3, 3, a2);
    std::cout << m1;

    Matrix<int> m2 = Matrix<int>(3, 3, a1) * !Matrix<int>(3, 3, a2);
    std::cout << m2;

    Matrix<double> m3 = Matrix<double>(3, 3, b1) * ~Matrix<double>(3, 3, b2);
    std::cout << m3;
}

// 1 1 1 6 -1 -2 1 -2 2 1 3 13
void drugi() {
    std::cout << "Drugi zadatak, unesi sustav: " << std::endl;
    double a[9], b[3];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            std::cin >> a[i*3+j];
        std::cin >> b[i];
    }
    std::cout << "[ x y z ] = " << !(~Matrix<double>(3, 3, a) * Matrix<double>(3, 1, b));
}

/*
 1 0 0
 5 0 0
 3 8 0
 3 4 0
 ------
 0.25 0.25 0.5
 */
void treci() {
    double a[9], t[3];
    for(int i = 0; i < 3; i++) {
        std::cout << "Tocka " << char('A' + (i % 3)) << ": " << std::endl;
        std::cin >> a[i] >> a[3+i] >> a[6+i];
    }
    std::cout << "Tocka T: " << std::endl;
    std::cin >> t[0] >> t[1] >> t[2];
    Matrix<> m1(3, 3, a);
    Matrix<> m2(3, 1, t);
    for(int i = 0; i < 3; i++)
        if(!m1(i, 0) && !m1(i, 1) && !m1(i, 2) && !m2(i, 0)) {
            m1(i, 0) = m1(i, 1) = m1(i, 2) = m2(i, 0) = 1;
            break;
        }
    std::cout << "Baricentricne koordinate: " << !(~m1 * m2) << std::endl;
}

int main(int argc, const char * argv[]) {
    prvi();
    drugi();
    treci();
    return 0;
}
