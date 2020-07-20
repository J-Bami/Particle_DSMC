#include <iostream>
#include "vector.h"
#include <cmath>
#include <cstring>
#include <cstdlib>
// constructors and destructors

Vector::Vector()
{
    m_length = 0;
    m_values = nullptr;
    //return;
}

Vector::Vector(const size_t length)
{
    m_length = length;
    m_values = new double [length];
    //return;
}

Vector::Vector(const Vector &vector)
{
    m_length = vector.m_length;
    m_values = new double [m_length]{};
    memcpy(m_values, vector.m_values, m_length*sizeof(double));
    return;
}

Vector::Vector(const double values[], const size_t length)
{
    
    m_length = length;
    m_values = new double[length];
    memcpy(m_values, values, m_length*sizeof(double));
    return;
}

Vector::~Vector()
{
    delete[] m_values;
    m_values = nullptr;
}

size_t Vector::get_length()const
{
    return m_length;
}

void Vector::set_length(const size_t new_length)
{
    void *ptr = realloc(m_values, new_length*sizeof(double));
    if ((!ptr) && (new_length != 0))
    {
        throw 2;
    }
    m_values = (double *)ptr;
    m_length = new_length;
    return;
}


bool Vector::same_length(const Vector &other)const
{
    return m_length == other.m_length;
}

//operators
double& Vector::operator[](const size_t index)const
{
    if (index >= m_length)
    {
        std::cout << "index " << index << "out of bounds";
        throw -1;
    }
    return m_values[index];
}

Vector& Vector::operator=(const Vector vector)
{
    m_length = vector.m_length;
    if (m_values == nullptr)

    {
        m_values = new double[m_length];
    }
    else
    {
        m_values = (double *) realloc(m_values, m_length*sizeof(double));
        if (m_values == nullptr)
        {
            throw 1;
        }
    }
    memcpy(m_values, vector.m_values, m_length*sizeof(double));
    return *this;
}


Vector& Vector::operator+=(const Vector &vector)
{
    if(!same_length(vector)){throw 1;}
    {
        for (size_t i = 0; i < m_length; i++)
        {
            m_values[i] += vector[i];
        }
    }
    return *this;
}

Vector& Vector::operator+=(const double scalar)
{
    for (size_t i = 0; i < m_length; i++)
    {
        m_values[i] += scalar;
    }
    return *this;
}

Vector& Vector::operator-=(const Vector &vector)
{
    if(!same_length(vector)){throw 1;}
    {
        for (size_t i = 0; i < m_length; i++)
        {
            m_values[i] -= vector[i];
        }
    }
    return *this;
}

Vector& Vector::operator-=(const double scalar)
{
    for (size_t i = 0; i < m_length; i++)
    {
        m_values[i] -= scalar;
    }
    return *this;
}

Vector& Vector::operator*=(const Vector &vector)
{
    if(!same_length(vector)){throw 1;}
    {
        for (size_t i = 0; i < m_length; i++)
        {
            m_values[i] *= vector[i];
        }
    }
    return *this;
}

Vector& Vector::operator*=(const double scalar)
{
    for (size_t i = 0; i < m_length; i++)
    {
        m_values[i] *= scalar;
    }
    return *this;
}


Vector& Vector::operator/=(const Vector &vector)
{
    if(!same_length(vector)){throw 1;}
    {
        for (size_t i = 0; i < m_length; i++)
        {
            m_values[i] /= vector[i];
        }
    }
    return *this;
}

Vector& Vector::operator/=(const double scalar)
{
    for (size_t i = 0; i < m_length; i++)
    {
        m_values[i] /= scalar;
    }
    return *this;
}

Vector::operator bool()const
{
    for (size_t i = 0; i < m_length; i++)
    {
        if (m_values[i])
        {
            return true;
        }
    }
    return false;
}

//vector-vector addition
Vector operator+(const Vector &v1, const Vector &v2)
{
    const size_t length = v1.get_length();
    if (!v1.same_length(v2))
    {
        throw 1;
    }
    Vector out(length);
    for (size_t i = 0; i < length; i++)
    {
        out[i] = v1[i] + v2[i];
    }
    return out;
}

//vector-scalar addition
Vector operator+(const Vector &vector, const double scalar)
{
    Vector out(vector.get_length());
    for (size_t i = 0; i < vector.get_length(); i++)
    {
        out[i] = vector[i] + scalar;
    }
    return out;
}

//scalar-vector addition
Vector operator+(const double scalar, const Vector &vector)
{
    return operator+(vector, scalar);
}


//vector-vector subtraction
Vector operator-(const Vector &v1, const Vector &v2)
{
    const size_t length = v1.get_length();
    if (length != v2.get_length())
    {
        throw 1;
    }
    Vector out(length);
    for (size_t i = 0; i < length; i++)
    {
        out[i] = v1[i] - v2[i];
    }
    return out;
}

//vector-scalar subtraction
Vector operator-(const Vector &vector, const double scalar)
{
    Vector out(vector.get_length());
    for (size_t i = 0; i < vector.get_length(); i++)
    {
        out[i] = vector[i] - scalar;
    }
    return out;
}

//scalar-vector subtraction
Vector operator-(const double scalar, const Vector &vector)
{
    Vector out(vector.get_length());
    for (size_t i = 0; i < vector.get_length(); i++)
    {
        out[i] = scalar - vector[i];
    }
    return out;
}

//vector-vector multiplication
Vector operator*(const Vector &v1, const Vector &v2)
{
    const size_t length = v1.get_length();
    if (length != v2.get_length())
    {
        throw 1;
    }
    Vector out(length);
    for (size_t i = 0; i < length; i++)
    {
        out[i] = v1[i] * v2[i];
    }
    return out;
}

//vector-scalar multiplication
Vector operator*(const Vector &vector, const double scalar)
{
    Vector out(vector.get_length());
    for (size_t i = 0; i < vector.get_length(); i++)
    {
        out[i] = vector[i] * scalar;
    }
    return out;
}

//scalar-vector multiplication
Vector operator*(const double scalar, const Vector &vector)
{
    return operator*(vector, scalar);
}


//vector-vector division
Vector operator/(const Vector &v1, const Vector &v2)
{
    const size_t length = v1.get_length();
    if (length != v2.get_length())
    {
        throw 1;
    }
    Vector out(length);
    for (size_t i = 0; i < length; i++)
    {
        out[i] = v1[i] / v2[i];
    }
    return out;
}

//vector-scalar division
Vector operator/(const Vector &vector, const double scalar)
{
    Vector out(vector.get_length());
    for (size_t i = 0; i < vector.get_length(); i++)
    {
        out[i] = vector[i] / scalar;
    }
    return out;
}

//scalar-vector division
Vector operator/(const double scalar, const Vector &vector)
{
    Vector out(vector.get_length());
    for (size_t i = 0; i < vector.get_length(); i++)
    {
        out[i] = scalar / vector[i];
    }
    return out;
}


bool operator==(const Vector &v1, const Vector &v2)
{
    if(v1.get_length() != v2.get_length()){return false;}
    for (size_t i = 0; i < v1.get_length(); i++)
    {
        if (v1[i] != v2[i])
        {
            return false;
        }
    }
    return true;
}

std::ostream& operator<< (std::ostream &out, const Vector &vector)
{
    out << "(";
    for (size_t i = 0; i < vector.m_length; i++)
    {
        out << vector.m_values[i];
        out << (i == vector.m_length-1? ")" : ", ");
    }
    return out;
}


Vector zeros(const size_t length)
{
    Vector out(length);
    for (size_t i = 0; i < length; i++)
    {
        out[i] = 0.0;
    }
    return out;
}

Vector ones(const size_t length)
{
    Vector out(length);
    for (size_t i = 0; i < length; i++)
    {
        out[i] = 1.0;
    }
    return out;
}

double mag2(const Vector &vector)
{
    double out{0.0};
    for (size_t i = 0; i < vector.get_length(); i++)
    {
        out += vector[i]*vector[i];
    }
    return out;
}

double mag(const Vector &vector)
{
    return pow(mag2(vector), 0.5);
}

Vector unit(const Vector &vector)
{
    return vector/mag(vector);
}


double dot(const Vector &v1, const Vector &v2)
{
    if(v1.get_length() != v2.get_length())
    {
        throw 1;
    }
    double out{0.0};
    for (size_t i = 0; i < v1.get_length(); i++)
    {
        out += v1[i]*v2[i];
    }
    return out;
}


Vector cross(const Vector &v1, const Vector &v2)
{
    if((v1.get_length() != v2.get_length()) || v1.get_length() != 3)
    {
        throw 1;
    }
    Vector out(3);
    out[0] = v1[1]*v2[2] - v1[2]*v2[1];
    out[1] = v1[2]*v2[0] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v1[1]*v2[0];
    return out;
}