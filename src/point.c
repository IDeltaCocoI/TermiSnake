#include "point.h"

#include <stdlib.h>

struct Point *create_point(int x, int y)
{
    struct Point *point = malloc(sizeof(struct Point));
    if (point)
    {
        point->x = x;
        point->y = y;
    }

    return point;
}

struct Point *add_points(struct Point *p1, struct Point *p2)
{
    p1->x += p2->x;
    p1->y += p2->y;

    return p1;
}
