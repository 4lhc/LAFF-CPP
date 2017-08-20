
/*
 *  lvectors.h
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Wed 09 Aug 2017 02:07:06 IST
 *  ver    :
 *
 */
#ifndef LVECTORS_H
#define LVECTORS_H


#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <string>


const double PI = atan(1) * 4;

class LaffVector
{
    typedef std::vector<double>::const_iterator const_iter;

    friend LaffVector operator*(const double &alpha, const LaffVector &v); //scale
    friend LaffVector operator+(const LaffVector &v1, const LaffVector &v2); //Add
    friend double Dot(const LaffVector &v1, const LaffVector &v2);
    friend double Norm2(const LaffVector &v);
    friend bool Equal(const LaffVector &v1, const LaffVector &v2);
    friend std::ostream &operator<<(std::ostream &os, const LaffVector &v);
    //friend std::istream &operator>>(std::istream &is, const LaffVector &v);

    protected:
    std::vector<double> _lvector{};
    std::string _name{};

    public:
    LaffVector(); //default
    LaffVector(int size); //construct vector of zeros
    LaffVector(int size, double elements); //construct vector of elements
    LaffVector(std::vector<double> v);
    LaffVector(std::vector<double> v, std::string &vname);
    ~LaffVector() {}

    double operator[](int index);
    LaffVector& Copy(LaffVector &v);
    LaffVector Slice(int start, int finish, int inc=1);
    LaffVector Transform(std::vector<std::vector<double>> &tr_mat);
    LaffVector Rotate(double angle);
    LaffVector Rotate(double angle, LaffVector &rot_axis);

    void Randomize(int l_range, int u_range, int digits=2); //populate with random elements
    //in range
    int Size() const {return _lvector.size();} //called by friends


};

#endif
