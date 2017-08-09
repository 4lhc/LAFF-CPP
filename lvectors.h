
/*
 *  lvectors.h
 *
 *  author : Sreejith S
 *  email  : echo $(base64 -d <<< NDQ0bGhjCg==)@gmail.com
 *  date   : Wed 09 Aug 2017 02:07:06 IST
 *  ver    :
 *
 */


#include<iostream>
#include<ctime>
#include<cmath>
#include<vector>


class LaffVector
{
    private:
        typedef std::vector<double>::const_iterator const_iter;
        std::vector<double> _lvector{};
        //construct with iterator values - used by simple slice method only
        LaffVector( const_iter it_begin, const_iter it_end)
            : _lvector( it_begin, it_end) {}


    public:
        LaffVector(int size); //construct vector of zeros
        LaffVector(std::vector<double> &v);
        ~LaffVector() {}

        LaffVector& LaffScale(double alpha);
        LaffVector& LaffCopy(LaffVector &v);
        LaffVector& LaffAxpy(double alpha, LaffVector &v);
        static double LaffDot(LaffVector &v1, LaffVector &v2);
        static double LaffNorm2(LaffVector &v);
        LaffVector LaffSlice(int start, int finish, int inc=1);

        void Display(); //print vector


        void Constant(double element);
        void Random(int l_range, int u_range, int digits=2); //populate with random elements
        //in range
        inline int Size() {return _lvector.size();}


};


LaffVector::LaffVector(int size)
    : _lvector(size, 0.0)
{}

LaffVector::LaffVector(std::vector<double> &v)
{ _lvector = v;}



void LaffVector::Display()
{
    //function to print the vector
    //
    //
    for(auto it = _lvector.begin(); it != _lvector.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

}

void LaffVector::Constant(double element)
{
    //populate the vector with constant elements
    //
    //
    //std::vector<int>::iterator it = _lvector.begin();
    auto it = _lvector.begin();
    auto it_end = _lvector.end();
    while(it != it_end)
    {
        *it = element;
        it++;
    }
}


void LaffVector::Random(int l_range, int u_range, int digits )
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

LaffVector& LaffVector::LaffScale( double alpha)
{
    //scale vector
    //x:=ax
    //
    auto it = _lvector.begin();
    auto it_end = _lvector.end();
    while(it != it_end)
    {
        *it *= alpha;
        it++;
    }
    return *this;

}

LaffVector& LaffVector::LaffCopy(LaffVector &v)
{
    //copy vector
    //y:=x
    //
    //check if they are equal length
    if (this->Size() != v.Size())
    {
        std::cerr << "Operation not permitted: size mismatch" << std::endl;
        return *this;
    }

    for(int i = 0; i<v.Size(); i++)
    {
        this->_lvector[i] = v._lvector[i];
    }

    return *this;
}


LaffVector& LaffVector::LaffAxpy(double alpha, LaffVector &v)
{
    //AXPY
    //y:=ax+y
    //
    //checking for equal length
    if (this->Size() != v.Size())
    {
        std::cerr << "Operation not permitted: size mismatch" << std::endl;
        return *this;
    }
    //scale v aka x by a
    LaffVector ax {v};
    ax.LaffScale(alpha);

    for(int i = 0; i<v.Size(); i++)
    {
        this->_lvector[i] += ax._lvector[i];
    }


    return *this;
}


double LaffVector::LaffDot( LaffVector &v1, LaffVector &v2)
{
    //Dot product
    //a:=x'y
    //
    //checking for equal length
    if (v1.Size() != v2.Size())
    {
        std::cerr << "Operation not permitted: size mismatch" << std::endl;
        return 0;
    }
    double aplha{};

    for(int i = 0; i<v1.Size(); i++)
    {
        aplha += v1._lvector[i] * v2._lvector[i];
    }

    return aplha;

}

double LaffVector::LaffNorm2(LaffVector &v)
{
    //Length of vector
    //a:=||x||2
    //
    return sqrt(LaffDot(v, v));
}

LaffVector LaffVector::LaffSlice(int start, int finish, int inc)
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
        std::cerr << "Illegal operation range" << std::endl;
        return *this;
    }
    return sliced_vector;
}
