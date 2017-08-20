/*
 *  vector_rotation.cpp
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Sun 20 Aug 2017 06:43:44 IST
 *  ver    :
 *
 */


#include <iostream>
#include "lvectors.h"
#include <iomanip>

int main()
{
    LaffVector v{{1, 0}};
    double theta{0};

    std::cout << "original vector:" << v  << std::endl;

    std::cin >> theta;
    std::cout << "rotated:" << v.Rotate(theta) << std::endl;

    //Rotate in 3D
    LaffVector v3{{1, 0, 0}}, rot_axis{{0, 0, 1}};
    std::cin >> theta;

    std::cout << "rotated:" << v3.Rotate(theta, rot_axis) << std::endl;


	return 0;
}
