
/*
module to look at all the particles in the environment at the current time
and predicts the time of the next collision, along with the particles that will
collide
*/
#include "predictor.h"

#include <cmath>

/*
predicts the time the two particles collide within the timestep. If the timestep is
0 or negative, we look for the next time from current time to infinity. Uses velocity
only, hence linear.
*/
double linear_predict(const Particle &p1, const Particle &p2, const double timestep)
{
    // first check if it's even possible for these to collide
    double sum_radii = p1.get_radius() + p2.get_radius();
    if (timestep > 0)
    {
        double distance = mag(p2.get_position() - p1.get_position());
        double tdv = timestep * (mag(p2.get_velocity()) + mag(p2.get_velocity()));

        // if the product time*|velocity| is less than distance, they won't collide
        // this timestep
        if (distance > (tdv + sum_radii)) {return -1;}
    }

    // solve the equation of two fat N-D lines crossing, with with r1+r2
    size_t dimension(p1.get_velocity().get_length());

    // express the difference in velocity and position as a 1-dimensional problem

    double dv2{};
    double dp2{};
    double dvdp{};

    Vector dv = p1.get_velocity() - p2.get_velocity();
    Vector dp = p1.get_position() - p2.get_position();
    for (size_t i = 0; i < dimension; i++)
    {
        dv2 = dv[i]*dv[i];
        dp2 = dp[i]*dp[i];
        dvdp = dv[i]*dp[i];
    }
    
    double det = dvdp*dvdp - dv2*(dp2 - sum_radii*sum_radii);
    if (det < 0)
    {
        return -1; // they don't collide - parallel lines.
    }

    double root_det = pow(det, 0.5);
    double time1 = -(dvdp + root_det)/dv2;
    double time2 = -(dvdp - root_det)/dv2;

    // return the smallest time larger than zero
    time1 = time1 > 0 ? time1 : 0;
    time2 = time2 > 0 ? time2 : 0;

    double out = time2 > time1 ? time2 : time1;

    return out ? out : -1;
}

/*
predicts the time of collision between a Line type and a particle
*/
double linear_predict(const Line &line, const Particle &p0, const double timestep)
{
    // first check if these *can* even collide:
    if (timestep > 0)
    {
        double distance = line.find_min_seperation(p0.get_position());
        double tdv = timestep*(mag(p0.get_velocity()));
        if (distance > (tdv + p0.get_radius()))
        {
            return -1;
        }
    }

    // solve the simultaneous equitong that define where the particle's center
    // crosses the axis collinear with the wall
    double px = line.get_pt1()[0];
    double py = line.get_pt1()[1];

    Vector axis = line.get_axis();
    double ax = axis[0]; double ay = axis[1];
    
    double xx = p0.get_position()[0]; double xy = p0.get_position()[1];
    double vx = p0.get_velocity()[0]; double vy = p0.get_velocity()[1];

    double time; 
    if(ax)
    {
        time = (ay*(xx-px)/ax + py - xy)/(vy - ay*vx/ax);
    }
    else
    {
        time = (ax*(xy-py)/ay + px - xx)/(vx - ax*vy/ay);
    }

    // now find the actual distance by using the position of the particle at time, and
    // equating to the line's position
    Vector position = p0.get_velocity()*time;
    position += p0.get_position();

    double seperation = line.find_min_seperation(position);
    if(seperation > p0.get_radius())
    {
        return -1;
    }

    // now that we know they collide, we step _back_ in time to figure out adjusted time
    time -= (p0.get_radius() - seperation)/mag(p0.get_velocity());
    return time <= 0? -1: time;
}