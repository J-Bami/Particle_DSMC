#include "../wall.h"

int main()
{
    double pt1[] = {0, 0};
    double pt2[] = {1, 0};
    Wall my_wall(pt1, pt2, 2);
    std::cout << my_wall;
    return 0;
}
