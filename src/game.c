#include "game.h"

#include <ncurses.h>
#include <stdlib.h>

#include "config.h"
#include "point.h"
#include "snake.h"
#include "string.h"

struct Game *new_game(struct Game *old_game)
{
    if (old_game)
    {
        free_game(old_game);
    }

    struct Game *game = malloc(sizeof(struct Game));
    if (!game)
    {
        return NULL;
    }

    struct Snake *snake = create_snake(COLS / 2, LINES / 2);
    if (!snake)
    {
        free_game(game);
        return NULL;
    }

    game->snake = snake;

    struct Point *apple = create_point(0, 0);
    if (!apple)
    {
        free_game(game);
        return NULL;
    }

    game->apple = apple;

    clear();
    spawn_apple(game);
    return game;
}

void free_game(struct Game *game)
{
    if (game->snake)
    {
        free_snake(game->snake);
    }

    if (game->apple)
    {
        free(game->apple);
    }

    free(game);
}

int pause_game(struct Game **game, int key)
{
    mvprintw(LINES / 2, (COLS / 2) - 3, "PAUSE");
    mvprintw((LINES / 2) + 1, (COLS / 2) - 12, "PRESS \"SPACE\" TO RESUME");
    mvprintw((LINES / 2) + 2, (COLS / 2) - 16,
             "PRESS \"ENTER\" TO RESTART A GAME");

    if (key == 'q')
    {
        return 1;
    }
    else if (key == 10) /* When "Enter" key is press */
    {
        *game = new_game(*game);
        if (!*game)
        {
            return 2;
        }
        return 3;
    }

    return 0;
}

void spawn_apple(struct Game *game)
{
    game->apple->x =
        (rand() % (COLS / (int)strlen(SNAKE_BODY))) * (int)strlen(SNAKE_BODY);
    game->apple->y = rand() % LINES;
}
