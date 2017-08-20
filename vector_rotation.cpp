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

    std::cout << "vector size (2 or 3): ";
    int n{};
    std::cin >> n;

    std::cout << "vector elements: ";
    std::vector<double> temp_v(n);
    for(int i = 0; i < n; i++)
    {
        std::cin >> temp_v[i];
    }

    LaffVector v{temp_v};


    double theta{0};
    std::cout << "Rotation angle: ";
    std::cin >> theta;

    if ( n == 2 )
    {
        //planar rotation about z axis
        std::cout << "Rotated vector:" << v.Rotate(theta) << std::endl;

    }
    else if ( n == 3)
    {

        std::cout << "Axis of rotation: ";
        for(int i = 0; i < n; i++)
        {
            std::cin >> temp_v[i];
        }

        LaffVector rot_axis{temp_v};
        std::cout << "Rotated vector:" << v.Rotate(theta, rot_axis) << std::endl;
    }
    else std::cout << "Not a 2D or 3D vector";

    return 0;
}
