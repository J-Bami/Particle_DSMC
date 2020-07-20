#ifndef LINE_H
#define LINE_H


#include <cstddef>
#include <iostream>
#include "vector.h"


/*
class that represents an N-dimensional line by copying vectors
*/

class Line
{
private:
    Vector pt1;
    Vector pt2;

    void set_pt1(const Vector &point);
    void set_pt2(const Vector &point);

public:
    Line();
    Line(const size_t dimension);
    Line(const double point1[], const double point2[], const size_t dimension);
    Line(const Vector &point1, const Vector &point2);
    Line(const Line &line);
    ~Line();
    void check_distinct_pts()const;
    Vector get_pt1()const;
    Vector get_pt2()const;
    double get_length()const;
    Vector get_axis()const;
    size_t get_dimension()const;

    double find_tstar(const Vector &point)const;
    Vector find_min_displacement(const Vector &point)const;
    double find_min_seperation(const Vector &point)const;

    Vector function(double t)const;

    Vector operator()(const double t)const;
    
    Line& operator=(const Line line);

    friend std::ostream& operator<<(std::ostream &out, const Line &line);
};


#endif