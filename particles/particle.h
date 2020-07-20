#ifndef PARTICLE_H
#define PARTICLE_H


/*
Defines a particle object.
*/

#include "../utility/vector.h"

class Particle
{
private:
    double m_radius;
    double m_mass;
    double m_elasticity;
    Vector m_position;
    Vector m_velocity;
public:
    Particle();
    Particle(const Vector position,
             const Vector velocity,
             const double mass,
             const double radius,
             const double elasticity=1);
    Particle(const Particle &particle);
    ~Particle();

    void set_velocity(const Vector &new_velocity);

    double get_mass()const;
    double get_elasticity()const;
    double get_radius()const;
    Vector get_position()const;
    Vector get_velocity()const;

    Vector momentum()const;
    double kinetic_energy()const;

    void update(const double timestep);
    double seperation(const Vector &point)const;
    double particle_seperation(const Particle &other)const;

    Particle& operator=(const Particle &particle);

    friend std::ostream& operator<<(std::ostream &out, const Particle &particle);
};

#define SIZEOF_PARTICLE sizeof(Particle)

#endif