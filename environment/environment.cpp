/*
does the time stepping of the simulation.

0) initialise envionment:
    -(read input)
    -initialise all boundaries
    -initialise particles & populate global particle list
    - for each particle:
        - check if collision between particle and all other objects is:
            - forward in time
            - earliest after global time
        - store the collision that satisfies both these requirements
1) time stepping loop:    
    - sort the collision array so that the collision that is earliest is first
    - advance time to the smallest of (next collision time, global timestep)
    - update all particles' positions
    - generate any new particles
    - if updated to environment timestep:
        - do the collision/interaction
        - remove all items from collision arrays with the *particle(s)* that just collided
        - add the next collisions with the particle(s) that just collided
2) That's everything
*/

#include "environment.h"
#include <stdlib.h>  // for qsort

int compare_collision(const void *ptr1, const void *ptr2)
{
    CollisionData *data1 = (CollisionData *)ptr1;
    CollisionData *data2 = (CollisionData *)ptr2;
    return (int)(data1->time > data2->id_2);
}

void sort_collision_data(CollisionData &data_array, const size_t length)
{
    qsort((void *)data_array, length, sizeof(CollisionData), compare_collision);
}
