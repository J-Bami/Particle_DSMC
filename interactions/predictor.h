#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "../particles/particle.h"
#include "../boundaries/wall.h"
double linear_predict(const Particle &p1, const Particle &p2, const double timestep);
double linear_predict(const Line &line, const Particle &p0, const double timestep);


#endif