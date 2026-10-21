#include "movement.h"

#include <ncurses.h>
#include <stddef.h>
#include <string.h>

#include "config.h"

struct Point *move_snake(struct Point *direction, int key)
{
    int dx = direction->x;
    int dy = direction->y;

    switch (key)
    {
    case 'q':
        return NULL;
    case 'w':
    case KEY_UP:
        if (dy == 0)
        {
            dx = 0;
            dy = -1;
        }
        break;
    case 's':
    case KEY_DOWN:
        if (dy == 0)
        {
            dx = 0;
            dy = 1;
        }
        break;
    case 'a':
    case KEY_LEFT:
        if (dx == 0)
        {
            dx = -1 * (int)strlen(SNAKE_BODY);
            dy = 0;
        }
        break;
    case 'd':
    case KEY_RIGHT:
        if (dx == 0)
        {
            dx = 1 * strlen(SNAKE_BODY);
            dy = 0;
        }
        break;
    }

    direction->x = dx;
    direction->y = dy;

    return direction;
}
