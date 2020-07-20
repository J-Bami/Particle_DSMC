#include "../collision.h"

int main()
{
    /* Make a wall, two particles and test the collision algorithms */
    double wall_pos1[2] = {0, 0};
    double wall_pos2[2] = {0, 1};

    double velocity_left[2] = {-5, 0};
    double v_down_right[2] = {1, -1};
    Vector v1(velocity_left, 2);
    Vector v2(v_down_right, 2);

    double right_pos[2] = {0.05, 0};
    double left_pos[2] = {-0.05, 0.1};
    Vector p1(right_pos, 2);
    Vector p2(left_pos, 2);

    // make the line
    Line wall_line = Line(wall_pos1, wall_pos2, 2);
    Wall wall = Wall(wall_line, 0.5, 0.1);

    Particle pa1(p1, v1, 1, 0.2);
    Particle pa2(p2, v2, 2, 0.3);
    std::cout << "\n\n";
    std::cout << pa1 << pa2 << "\ndoing particle particle collision:\n\n";
    collision(pa1, pa2);
    std::cout << '\n' << pa1 << pa2;

    std::cout << "\n\n";
    std::cout << wall << pa2 << "\ndoing wall particle collision:\n\n";
    collision(wall, pa2);
    std::cout << wall << pa2;

    return 0;
}
