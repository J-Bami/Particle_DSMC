#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>



/* Defines a class for a fixed-size, 1-D mathematical array*/


class Vector
{
private:
    size_t m_length;
    double *m_values;
public:

    //initialisers
    Vector();
    Vector(const size_t length);
    Vector(const double values[], const size_t length);
    Vector(const Vector &vector);

    ~Vector();

    //getters
    size_t get_length()const;

    //setters
    void set_length(const size_t new_length);

    bool same_length(const Vector &other)const;

    //operators
    operator bool()const;
    double& operator[](const size_t index)const;

    Vector& operator=(const Vector vector);

    Vector& operator+=(const Vector &vector);
    Vector& operator+=(const double scalar);

    Vector& operator-=(const Vector &vector);
    Vector& operator-=(const double scalar);

    Vector& operator*=(const Vector &vector);
    Vector& operator*=(const double scalar);

    Vector& operator/=(const Vector &vector);
    Vector& operator/=(const double scalar);

    friend std::ostream& operator<<(std::ostream &out, const Vector &vector);

};

Vector operator+(const Vector &v1, const Vector &v2);
Vector operator+(const Vector &vector, const double scalar);
Vector operator+(const double scalar, const Vector &vector);


Vector operator-(const Vector &v1, const Vector &v2);
Vector operator-(const Vector &vector, const double scalar);
Vector operator-(const double scalar, const Vector &vector);

Vector operator*(const Vector &v1, const Vector &v2);
Vector operator*(const Vector &vector, const double scalar);
Vector operator*(const double scalar, const Vector &vector);



Vector operator/(const Vector &v1, const Vector &v2);
Vector operator/(const Vector &vector, const double scalar);
Vector operator/(const double scalar, const Vector &vector);


bool operator==(const Vector &v1, const Vector &v2);

Vector zeros(const size_t length);
Vector ones(const size_t length);

double mag2(const Vector &vector);
double mag(const Vector &vector);
Vector unit(const Vector &vector);

double dot(const Vector &v1, const Vector &v2);
Vector cross(const Vector &v1, const Vector &v2);

#define SIZEOF_VECTOR ((size_t) sizeof(Vector))

#endif //VECTOR_H
