#include "line.h"

Line::Line()
{
    pt1 = Vector();
    pt2 = Vector();
    return;
}


// makes a line with no references. works
Line::Line(const size_t dimension)
{
    pt1 = Vector{dimension};
    pt2 = Vector{dimension};
    return;
}

// makes the vectors it references. not working.
Line::Line(const double point1[], const double point2[], const size_t dimension)
{
    // initialise vectors...
    pt1 = Vector(point1, dimension);
    pt2 = Vector(point2, dimension);
    check_distinct_pts();
    return;
}

// copies
Line::Line(const Vector &point1, const Vector &point2)
{
    pt1 = Vector(point1);
    pt2 = Vector(point2);
    check_distinct_pts();
    return;
}


// copy inititalisation
Line::Line(const Line &line)
{
    pt1 = Vector(line.pt1);
    pt2 = Vector(line.pt2);
    check_distinct_pts();
    return;
}

Line::~Line()
{
    return;
}

void Line::set_pt1(const Vector &point)
{
    pt1 = Vector(point);
    check_distinct_pts();
    return;
}


void Line::set_pt2(const Vector &point)
{
    pt2 = Vector(point);
    check_distinct_pts();
    return;
}

void Line::check_distinct_pts()const
{
    if(pt1 == pt2)
    {
        std::cout << pt1 << " == " << pt2;
        throw 1;
    }
    return;
}

// returns a copy
Vector Line::get_pt1()const
{
    return pt1;
}

Vector Line::get_pt2()const
{
    return pt2;
}

double Line::get_length()const
{
    return mag(pt2 - pt1);
}

Vector Line::get_axis()const
{
    return (get_pt2() - get_pt1());
}

size_t Line::get_dimension()const
{
    return pt1.get_length();
}


/*
finds the value of the parameter that returns the closest position on the line
when input into line.function
*/
double Line::find_tstar(const Vector &point)const
{
    Vector axis = get_axis();
    return dot(point - pt1, axis)/mag2(axis);
}

// gets the absolute position using a line parameter
Vector Line::function(double t)const
{
    t = t > 1.0 ? 1.0 : t < 0.0 ? 0.0 :t;
    return pt1 + (t * get_axis());
}

//finds the minimum displacement between the line and point
Vector Line::find_min_displacement(const Vector &point)const
{
    return point - function(find_tstar(point));
}

//finds the magnitude of the minimum displacement between line and point
double Line::find_min_seperation(const Vector &point)const
{
    return mag(find_min_displacement(point));
}

//Can call Line a function
Vector Line::operator()(const double t)const
{
    return function(t);
}


// output
std::ostream& operator<<(std::ostream &out, const Line &line)
{
    out << line.get_dimension() << "-D Line: " << line.pt1 << ", " <<line.pt2 <<"\n";
    return out;
}


Line& Line::operator=(const Line line)
{
    //copy everything across
    pt1 = line.pt1;
    pt2 = line.pt2;
    return *this;
}