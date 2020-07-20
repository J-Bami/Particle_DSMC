
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "/../particles/particle.h"
#include "/../boundaries/wall.h"
#include "/../boundaries/outlet.h"
#include "/../boundaries/inlet.h"
#include <cstddef>


// contains the 
typedef struct CollisionData
{
public:
    void *id_1;
    void *id_2;
    double time;
    int flag;  // indicates the kind of interaction we have.
}CollisonData;

int compare_collision(const void *ptr1, const void *ptr2);
void sort_collision_data(CollisionData &data_array, const size_t length);


#endif //ENVIRONMENT_H