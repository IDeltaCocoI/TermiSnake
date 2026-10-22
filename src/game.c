#include "game.h"

#include <ncurses.h>
#include <stdlib.h>

#include "snake.h"

struct Game *new_game()
{
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

    return game;
}

void free_game(struct Game *game)
{
    if (game->snake)
    {
        free_snake(game->snake);
    }

    free(game);
}
