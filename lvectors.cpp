
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

LaffVector::LaffVector()
    : _lvector(0)
{}
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



double LaffVector::operator[](int index)
{
    return _lvector[index];
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

LaffVector LaffVector::Transform(std::vector<std::vector<double>> &tr_mat)
{
    //TODO: match size of transformation_matrix to vector
    std::vector<LaffVector> transformation_matrix;
    LaffVector transformed_vector;
    if ( Size() == 2)
    {
        transformation_matrix = {{tr_mat[0]}, {tr_mat[1]}};
        auto &tm = transformation_matrix;
        transformed_vector = {{ Dot(tm[0], *this), Dot(tm[1], *this) }};
    }

    else if ( Size() == 3)
    {
        transformation_matrix = {{tr_mat[0]}, {tr_mat[1]}, {tr_mat[2]}};
        auto &tm = transformation_matrix;
        transformed_vector = {{ Dot(tm[0], *this), Dot(tm[1], *this), Dot(tm[2], *this) }};
    }

    else
    {
        throw std::invalid_argument("Not a 2D or 3D vector");
    }

    return transformed_vector;
}




LaffVector LaffVector::Rotate(double angle, LaffVector &rot_axis)
{
    //https://en.wikipedia.org/wiki/Euler–Rodrigues_formula

    double a{}, b{}, c{}, d{};
    angle *= PI/180;

    LaffVector unit_axis = (1/Norm2(rot_axis))*rot_axis;
    double kx = unit_axis[0];
    double ky = unit_axis[1];
    double kz = unit_axis[2];

    a = cos(angle/2);
    b = kx*sin(angle/2);
    c = ky*sin(angle/2);
    d = kz*sin(angle/2);


    std::vector<std::vector<double>> tr_mat{
        {a*a + b*b - c*c - d*d, 2*(b*c - a*d), 2*(b*d + a*c)},
        {2*(b*c + a*d), a*a - b*b + c*c - d*d,  2*(c*d - a*b)},
        {2*(b*d - a*c), 2*(c*d + a*b), a*a - b*b - c*c + d*d}};

    double limit = 0.0002;
    for(unsigned int i = 0; i < tr_mat.size(); i++)
    {
        for(unsigned int j=0; j < tr_mat[i].size(); j++)
        {
            if (fabs(tr_mat[i][j]) <= limit) tr_mat[i][j] = 0;
        }
    }

    return this->Transform(tr_mat);
}


LaffVector LaffVector::Rotate(double angle)
{

    LaffVector rot_axis{{0, 0, 1}}; //rotated around z axis
    _lvector.push_back(0); //add zero to make the size 3
    LaffVector rotated_vector =  Rotate(angle, rot_axis);
    rotated_vector._lvector.pop_back(); //reduce the size back to 2
    return rotated_vector;

}


