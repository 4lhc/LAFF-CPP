/*
 *  1.8.1.2_Homework.cpp
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Thu 10 Aug 2017 00:58:45 IST
 *  ver    :
 *
 *   http://edx-org-utaustinx.s3.amazonaws.com/UT501x/Summer2015/Notes/Week1.pdf#page=38
 */


#include <string>
#include "lvectors.h"
#include <algorithm>


LaffVector City(int x_deg, int x_min, int y_deg, int y_min, std::string cname)
{

    std::vector<double> cv{x_deg*60.0 + x_min, y_deg*60.0 + y_min};
    LaffVector city_vec(cv, cname);
    //LaffVector city_vec({x_deg*60.0 + x_min, y_deg*60.0 + y_min});
    return city_vec;
}

LaffVector City(int x_deg, int x_min, int y_deg, int y_min)
{

    std::vector<double> cv{x_deg*60.0 + x_min, y_deg*60.0 + y_min};
    LaffVector city_vec(cv);
    //LaffVector city_vec({x_deg*60.0 + x_min, y_deg*60.0 + y_min});
    return city_vec;
}

int main()
{

    //std::vector<std::string> city_names{"London", "Pisa", "Valencia", "Zurich", "Austin", "Brussels", "Darmstadt", "Krakov"};
    std::vector<LaffVector> city_list{};
    city_list.push_back(City( 0, -8,  51, 30, "London"));
    city_list.push_back(City( 10, 21,  43, 43, "Pisa"));
    city_list.push_back(City( 0, 23,  39, 28, "Valencia" ));
    city_list.push_back(City( 8, 33,  47, 22, "Zurich" ));
    city_list.push_back(City( -97, -45,  30, 15, "Austin" ));
    city_list.push_back(City( 4, 21,  50, 51, "Brussels"));
    city_list.push_back(City( 8, 39,  49, 52, "Darmstadt" ));
    city_list.push_back(City( 19, 56,  50, 4, "Krakov" ));


    std::vector<LaffVector> path_list{};
    path_list.push_back(City(102, 6, 20, 36 ));
    path_list.push_back(City( 4, 18, 0, -59 ));
    path_list.push_back(City( 0, -6, -2, -30 ));
    path_list.push_back(City( 1, 48, -3, -39 ));
    path_list.push_back(City( 9, 35,  6, 21 ));
    path_list.push_back(City( -20, -4, 1, 26 ));
    path_list.push_back(City( 0, 31,  -12, -2 ));
    path_list.push_back(City( -98, -8,  -9, -13));

    //City next_city();
    LaffVector curr_city(City( -97, -45,  30, 15, "Austin" ));

    //if (Equal(curr_city, city_list[1]))
    //std::cout << city_list[4];
    std::cout << curr_city;
    for (unsigned int i = 0; i < path_list.size(); i++)
    {
        LaffVector next_city = curr_city + path_list[i];
        for (unsigned int j = 0; j < city_list.size(); j++)
        {
            if (Equal(next_city, city_list[j]))
            {
                //found next city
                std::cout << city_list[j];
                curr_city = next_city;
            }
        }
    }
}
