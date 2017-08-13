
/*
 *  lvectors.cpp
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Wed 09 Aug 2017 02:07:06 IST
 *  ver    :
 *
 */


#include "lvectors.h"

int main()
{

    //zero vector x of size 5
    LaffVector x{5};
    //populate with random numbers in the range 0 to 10: to 3 decimal points
    x.Randomize(0, 10, 3);
    std::cout << "x: " << x;

    //Populate with constant values
    LaffVector y{5, 1.1};
    //SCAL: scale x with 0.5
    std::cout << "2 * y: " << y;

    LaffVector xc{5};
    //COPY
    xc = xc.Copy(x);
    std::cout << "xc " << xc;

    //Define a LaffVector z with a vector
    //std::vector<double> v{1.2, 2.3, 4.21, 1.3, 1.0};
    LaffVector z{{1.2, 2.3, 4.21, 1.3, 1.0}};
    std::cout << "z: " << z;

    //ADD
    //
    std::cout << " x + y: " << (x + y);


    //AXPY
    //z = 1.5*x + y
    std::cout << "AXPY: 1.5x + y: " << ((1.5*x ) + y);

    //Linear combination of vectors
    std::cout << "x + 2y + 3z: " << (x + (2*y) + (3*z));

    //DOT & NORM2
    std::cout << "dot(x, y) = " << Dot(x, y) << std::endl;
    std::cout << "length(x) = " << Norm2(x) << std::endl;
    std::cout << "length(y) = " << Norm2(y) << std::endl;

    LaffVector r(10);
    r.Randomize(0, 50);
    std::cout << "r: " << r;


    //SLICE
    LaffVector forward_slice = r.Slice(2, 5, 1);
    LaffVector reverse_slice = r.Slice(8, 3, -2); //with stride -2

    std::cout << "Slice(2, 5, 1): " << forward_slice;
    std::cout << "Slice(8, 3, -2): " << reverse_slice;

    return 0;
}
