#ifndef WALL
#define WALL

#include "../utility/line.h"

class Wall: public Line
{
private:
    double m_elasticity;  // 0 to 1
    double m_friction; // 0 to 1
public:
    Wall(const double point1[], const double point2[], const size_t dimension,
         double elasticity=1, double friction=0);
    Wall(const Vector point1, const Vector point2,
         double elasticity=1, double friction=0);
    Wall(const Line &line, double elasticity=1, double friction=0);
    Wall(const Wall &wall);
    ~Wall();

    double get_elasticity()const;
    double get_friction()const;

    Wall& operator=(const Wall wall);
    friend std::ostream& operator<<(std::ostream &out, const Wall &wall);
};

#endif //INLET_H
