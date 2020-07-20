/*
Module to define the different kinds of interactions that Particles can have with the
different kinds of boundaries and other particles.
Restricted only to reflections with walls and other particles for now
*/

#include "collision.h"
#include <cmath>

/*
does the momentum exchange for two particles that collide. assumes the particles
are already touching
*/
void collision(Particle &p1, Particle &p2)
{
    /*
    convert this into a 1-dimensional collision by finding the normal:
    the relative displacement of the particle centers is the normal vector to both
    */
    const Vector normal = unit(p1.get_position() - p2.get_position());

    //get masses to reduce typing:
    const double m1 = p1.get_mass();
    const double m2 = p2.get_mass();

    //find the ratio of total KE before to after:
    const double ratio = p1.get_elasticity() * p2.get_elasticity();

    // convert velocities to scalars:
    const double u1 = dot(normal, p1.get_velocity());
    const double u2 = dot(normal, p2.get_velocity());

    // solve the 1-D quadratic momentum/KE simultaneous equations
    const double alpha = (m2 + m2*m2/m1);
    const double beta = -2*(u1*m2 + u2*m2*m2/m1);
    const double gamma = m2*m2*u2*u2/m1 + 2*u1*m2*u2 + m1*u1*u1 - ratio*(m1*u1*u1 + m2*u2*u2);

    const double rootdet = pow(beta*beta - 4*alpha*gamma, 0.5);

    // new velocities
    const double v2 = (-beta - rootdet)/(2*alpha);
    const double v1 = u1 + m2*(u2-v2)/m1;

    // subtract the old normal velocities from the old velocities,
    // and add the new ones
    Vector du1 = normal*(v1-u1);
    Vector du2 = normal*(v2-u2);

    std::cout << du1 << du2 << normal <<" " << v1  <<" " << v2<<"\n";

    // set the new velocities
    p1.set_velocity(p1.get_velocity() + du1);
    p2.set_velocity(p2.get_velocity() + du2);
    return;
}

/*
does the momentum exchange for a wall-particle collision. Walls have assumed infinite
mass, particles are reflected. Assumes the particle & wall are touching.
*/
void collision(Wall &wall, Particle &p0)
{
    /*
    again, convert this into a 1-dimensional collision by finding the normal,
    which is taken as the displacement between the centre of the particle and
    the closest point on the line inside wall.
    */
    const Vector normal = unit(wall.find_min_displacement(p0.get_position()));

    //seperate the particle's velocity into tangential and normal components:
    Vector normal_velocity = normal * dot(p0.get_velocity(), normal);
    Vector tangential_velocity = p0.get_velocity() - normal_velocity;

    //Calculate the new velocity
    Vector new_velocity = tangential_velocity*(1 - wall.get_friction()) -
        normal_velocity*wall.get_elasticity()*p0.get_elasticity();

    //set the new velocity
    p0.set_velocity(new_velocity);
    return;
}

