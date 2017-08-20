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

	return 0;
}
