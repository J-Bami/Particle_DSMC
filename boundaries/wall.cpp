#include "wall.h"


/*
initialises by making the line it sits on from the double arrays representing
its points
*/
Wall::Wall(const double point1[], const double point2[], const size_t dimension,
           double elasticity, double friction):
         Line{point1, point2, dimension},
         m_elasticity{elasticity}, m_friction{friction}
{
    m_elasticity > 1 ? 1 : m_elasticity < 0 ? 0 : m_elasticity;
    m_friction > 1 ? 1 : m_friction < 0 ? 0 : m_friction;
    return;
}

//initialises from the vectors describing its points
Wall::Wall(const Vector point1, const Vector point2,
           double elasticity, double friction):
           Line{point1, point2},
           m_elasticity{elasticity}, m_friction{friction}
{
    m_elasticity > 1 ? 1 : m_elasticity < 0 ? 0 : m_elasticity;
    m_friction > 1 ? 1 : m_friction < 0 ? 0 : m_friction;
    return;
}

//initialises directly from the line
Wall::Wall(const Line &line, double elasticity, double friction):
           Line{line},
           m_elasticity{elasticity}, m_friction{friction}
{
    m_elasticity > 1 ? 1 : m_elasticity < 0 ? 0 : m_elasticity;
    m_friction > 1 ? 1 : m_friction < 0 ? 0 : m_friction;
    return;
}

Wall::~Wall()
{
}

double Wall::get_elasticity()const
{
    return m_elasticity;
}


double Wall::get_friction()const
{
    return m_friction;
}


std::ostream& operator<<(std::ostream &out, const Wall &wall)
{
    out << "Wall, Elasticity: "<< wall.m_elasticity << ", friction coefficient:"
    << wall.m_friction << " pt1:" << wall.get_pt1() << " pt2:" << wall.get_pt2() << "\n";
    return out;
}