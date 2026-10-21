#ifndef POINT_H
#define POINT_H

struct Point
{
    int x;
    int y;
};

struct Point *create_point(int x, int y);

/* Add p1 and p2 into p1 */
struct Point *add_points(struct Point *p1, struct Point *p2);

#endif
