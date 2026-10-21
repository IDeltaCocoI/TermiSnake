#include "snake.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

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
        body[i] = create_point(start_x - i * (int)strlen(SNAKE_BODY), start_y);
        if (!body[i])
        {
            free_snake(snake);
            return NULL;
        }
    }

    struct Point *direction =
        create_point(DEFAULT_DIRECTION_X, DEFAULT_DIRECTION_Y);
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
    for (size_t i = snake->length - 1; i > 0; --i)
    {
        snake->body[i]->x = snake->body[i - 1]->x;
        snake->body[i]->y = snake->body[i - 1]->y;
    }

    snake->body[0]->x =
        (((snake->body[0]->x + snake->direction->x * (int)strlen(SNAKE_BODY)) % COLS) + COLS) % COLS;
    snake->body[0]->y =
        (((snake->body[0]->y + snake->direction->y) % LINES) + LINES) % LINES;
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
