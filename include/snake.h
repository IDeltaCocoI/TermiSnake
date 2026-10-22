#ifndef SNAKE_H
#define SNAKE_H

#include <stddef.h>
#include "point.h"

struct Snake
{
    struct Point **body;
    struct Point *direction;
    size_t length;
};

struct Snake *create_snake(int start_x, int start_y);
void update_snake(struct Snake *snake);
void free_snake(struct Snake *snake);
struct Snake *grow_snake(struct Snake *snake);

#endif
