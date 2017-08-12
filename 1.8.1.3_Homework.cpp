/*  
 *  1.8.1.3_Homework.cpp
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Sun 13 Aug 2017 01:48:42 IST
 *  ver    : 
 *   
 */


#include "lvectors.h"


int main()
{

    LaffVector avg_power({90, 30, 10, 15, 5});
    LaffVector frac_time({0.7, 0.6, 0.3, 0.1, 1.0});
    std::cout << Dot((0.001*avg_power), (2*frac_time));

	return 0;
}
