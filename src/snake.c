#include "snake.h"

#include <stdlib.h>

#include "config.h"
#include "point.h"

struct Snake *create_snake(int start_x, int start_y)
{
    struct Snake *snake = malloc(sizeof(struct Snake));
    if (!snake)
    {
        return NULL;
    }

    struct Point **body = malloc(INITIAL_LENGTH * sizeof(struct Point *));
    if (!body)
    {
        free_snake(snake);
        return NULL;
    }

    snake->body = body;
    snake->length = INITIAL_LENGTH;

    for (size_t i = 0; i < INITIAL_LENGTH; ++i)
    {
        body[i] = malloc(sizeof(struct Point));
        if (!body)
        {
            free_snake(snake);
            return NULL;
        }

        body[i]->x = start_x - i;
        body[i]->y = start_y;
    }

    struct Point *direction = malloc(sizeof(struct Point));
    if (!direction)
    {
        free_snake(snake);
        return NULL;
    }

    snake->direction = direction;

    return snake;
}

void update_snake(struct Snake *snake)
{
    for (size_t i = snake->length - 1; i > 0; ++i)
    {
        snake->body[i]->x = snake->body[i - 1]->y;
        snake->body[i]->y = snake->body[i - 1]->y;
    }

    add_points(snake->body[0], snake->direction);
}

void free_snake(struct Snake *snake)
{
    if (snake->body)
    {
        for (size_t i = 0; i < snake->length; ++i)
        {
            if (snake->body[i])
            {
                free(snake->body[i]);
            }
        }
    }

    if (snake->direction)
    {
        free(snake->direction);
    }

    free(snake);
}
