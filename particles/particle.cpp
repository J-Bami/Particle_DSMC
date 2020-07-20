#include "particle.h"
#include <cmath>

//default constructor for particle
Particle::Particle()
{
    m_radius = 0;
    m_mass = 0;
    m_elasticity = 1.0;
    m_position = Vector();
    m_velocity = Vector();
    return;
}


//for the particle generators
Particle::Particle(const Vector position,
             const Vector velocity,
             const double mass,
             const double radius,
             const double elasticity)
{
    m_position = position;
    m_velocity = velocity;
    m_mass = fabs(mass);
    m_radius = fabs(radius);
    m_elasticity = elasticity > 1 ? 1 : elasticity < 0 ? 0: elasticity;
    return;
}


// copies all the information about the particle
Particle::Particle(const Particle &particle)
{
    m_elasticity = particle.m_elasticity;
    m_mass = particle.m_mass;
    m_radius = particle.m_radius;
    m_velocity = particle.m_velocity;
    m_position = particle.m_velocity;
}

Particle::~Particle()
{
    m_velocity.~Vector();
    m_position.~Vector();
    return;
}

void Particle::set_velocity(const Vector &new_velocity)
{
    m_velocity.~Vector();
    m_velocity = new_velocity;
    return;
}


double Particle::get_mass()const
{
    return m_mass;
}

double Particle::get_elasticity()const
{
    return m_elasticity;
}


double Particle::get_radius()const
{
    return m_radius;
}


Vector Particle::get_position()const
{
    return m_position;
}

Vector Particle::get_velocity()const
{
    return m_velocity;
}

Vector Particle::momentum()const
{
    return m_velocity*m_mass;
}

double Particle::kinetic_energy()const
{
    return mag2(m_velocity)*(m_mass*0.5);
}

void Particle::update(const double timestep)
{
    m_position += (m_velocity*timestep);
}

double Particle::seperation(const Vector &point)const
{
    return mag(m_position - point);
}

// finds the seperation between two particles
double Particle::particle_seperation(const Particle &other)const
{
    double combined_radius = m_radius + other.m_radius;
    return seperation(other.m_position) - combined_radius; // allow this to have -ve values
}

Particle& Particle::operator=(const Particle &particle)
{
    m_elasticity = particle.m_elasticity;
    m_mass = particle.m_mass;
    m_radius = particle.m_radius;
    m_velocity = particle.m_velocity;
    m_position = particle.m_velocity;
    return *this;
}

std::ostream& operator<<(std::ostream &out, const Particle &particle)
{
    out << "Particle, radius: " << particle.m_radius << ", mass:" << particle.m_mass <<
    ", position= " << particle.m_position << ", Velocity= " << particle.m_velocity << "\n";
    return out;
}