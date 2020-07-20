#ifndef COLLISION_H
#define COLLISION_H

#include "../particles/particle.h"
#include "../boundaries/wall.h"

void collision(Particle &p1, Particle &p2);
void collision(Wall &wall, Particle &p0);


#endif // COLLISION_H