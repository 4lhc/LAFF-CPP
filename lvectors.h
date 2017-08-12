
/*
 *  lvectors.h
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Wed 09 Aug 2017 02:07:06 IST
 *  ver    :
 *
 */


#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <string>


class LaffVector
{
    typedef std::vector<double>::const_iterator const_iter;

    friend LaffVector operator*(const double &alpha, const LaffVector &v); //scale
    friend LaffVector operator+(const LaffVector &v1, const LaffVector &v2); //Add
    friend double Dot(const LaffVector &v1, const LaffVector &v2);
    friend double Norm2(const LaffVector &v);
    friend bool Equal(const LaffVector &v1, const LaffVector &v2);
    friend std::ostream &operator<<(std::ostream &os, const LaffVector &v);

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

    LaffVector& Copy(LaffVector &v);
    LaffVector Slice(int start, int finish, int inc=1);

    void Randomize(int l_range, int u_range, int digits=2); //populate with random elements
    //in range
    int Size() const {return _lvector.size();} //called by friends


};

LaffVector::LaffVector()
    : _lvector(0)
{}
//Constructor definition
LaffVector::LaffVector(int size)
    : _lvector(size, 0.0)
{}

LaffVector::LaffVector(int size, double elements)
    : _lvector(size, elements)
{}

LaffVector::LaffVector(std::vector<double> v)
    : _lvector(v)
{}

LaffVector::LaffVector(std::vector<double> v, std::string &vname)
    : _lvector(v), _name(vname)
{}

LaffVector& LaffVector::Copy(LaffVector &v)
{
    //copy vector
    //y:=x
    //
    //check if they are equal length
    if (this->Size() != v.Size())
    {

        throw std::invalid_argument("Size mismatch");
    }

    for(int i = 0; i<v.Size(); i++)
    {
        this->_lvector[i] = v._lvector[i];
    }

    return *this;
}





LaffVector LaffVector::Slice(int start, int finish, int inc)
{
    //Slice a vector
    //
    //

    LaffVector sliced_vector(0);
    //LaffVector sliced_vector(abs(finish-start)+1);
    if (inc >= 0 && finish >= start)
    {
        const_iter it_begin = _lvector.begin() + start;
        const_iter it_end = _lvector.begin() + finish + 1;
        auto it = it_begin;
        while (it != it_end)
        {
            sliced_vector._lvector.push_back(*it);
            it += inc;
        }
    }
    else if (inc < 0 && finish <= start)
    {
        const_iter it_begin = _lvector.begin() + start;
        const_iter it_end = _lvector.begin() + finish - 1;
        auto it = it_begin;
        while (it != it_end)
        {
            sliced_vector._lvector.push_back(*it);
            it -= abs(inc);

        }
    }
    else
    {
        throw std::invalid_argument("Illegal range");
    }
    return sliced_vector;
}


void LaffVector::Randomize(int l_range, int u_range, int digits )
{
    //populate with random elements
    //
    //
    srand(time(NULL)); //init seed
    auto it = _lvector.begin();
    auto it_end = _lvector.end();
    int mf = pow(10, digits); //decimal points mult_factor
    while(it != it_end)
    {

        *it =  static_cast<double>(rand() % (u_range * mf) + l_range * mf)/mf;
        it++;
    }

}

LaffVector operator*(const double &alpha, const LaffVector &v)
{
    //scale vector
    //x:=ax
    //
    LaffVector scaled_v = v;
    auto it = scaled_v._lvector.begin();
    auto it_end = scaled_v._lvector.end();
    while(it != it_end)
    {
        *it *= alpha;
        it++;
    }
    return scaled_v;

}

LaffVector operator+(const LaffVector &v1, const LaffVector &v2)
{
    //x+y
    //
    //checking for equal length
    LaffVector added_v= v1;
    if (v2.Size() != v1.Size())
    {
        throw std::invalid_argument("Size mismatch");
    }

    for(unsigned int i = 0; i<v1._lvector.size(); i++)
    {
        added_v._lvector[i] = v1._lvector[i] + v2._lvector[i];
    }


    return added_v;
}


double Dot(const LaffVector &v1, const LaffVector &v2)
{
    //Dot product
    //a:=x'y
    //
    //checking for equal length
    if (v1.Size() != v2.Size())
    {
        throw std::invalid_argument("Size mismatch");
    }
    double aplha{0};

    for(int i = 0; i<v1.Size(); i++)
    {
        aplha += v1._lvector[i] * v2._lvector[i];
    }
    return aplha;
}



double Norm2(const LaffVector &v)
{
    //Length of vector
    //a:=||x||2
    //
    return sqrt(Dot(v, v));
}


bool Equal(const LaffVector &v1, const LaffVector &v2)
{
    //check if two vectors are equal
    bool are_equal = false;
    if (v1.Size() == v2.Size())
    {
        are_equal = true;
        for (int i = 0; i < v1.Size(); i++)
        {
            if (v1._lvector[i] != v2._lvector[i])
            {
                are_equal = false;
                break;
            }
        }
    }
    return are_equal;
}


std::ostream &operator<<(std::ostream &output, const LaffVector &v)
{

    if (v._name.size() > 0)
        output << v._name << ": ";
    output << "( ";
    for(auto it = v._lvector.begin(); it != v._lvector.end(); it++)
        output << *it << " ";
    output << " )\n";
    return output;
}

