
/*
 *  lvectors.cpp
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Wed 09 Aug 2017 02:07:06 IST
 *  ver    :
 *
 */


#include <iostream>
#include "lvectors.h"

int main()
{

    //zero vector x of size 5
    LaffVector x(5);
    //Populate with constant integers
    x.Constant(1.01);
    //populate with random numbers in the range 0 to 10: to 3 decimal points
    x.Random(0, 10, 3);
    //scale x with 0.5
    x.LaffScale(0.5);
    x.Display();

    std::vector<double> v{1.2, 2.3, 4.21, 1.3, 1.0};
    //Define a vector y with v
    LaffVector y(v);
    y.Display();

    std::cout << "dot(x, y) = " << LaffVector::LaffDot(x, y) << std::endl;
    std::cout << "length(x) = " << LaffVector::LaffNorm2(x) << std::endl;
    std::cout << "length(y) = " << LaffVector::LaffNorm2(y) << std::endl;

    LaffVector z(10);
    z.Random(0, 10);
    //z.LaffScale(1.23);
    z.Display();

    LaffVector forward_slice = z.LaffSlice(2, 5, 1);
    LaffVector reverse_slice = z.LaffSlice(8, 3, -2); //with stride -2

    forward_slice.Display();
    reverse_slice.Display();

    return 0;
}