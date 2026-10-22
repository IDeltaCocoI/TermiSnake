#include "game.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "movement.h"
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
    game->score = 0;
    game->status = PLAYING;

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

int update_game(struct Game *game, int key)
{
    if (game->status == PLAYING)
    {
        if (move_snake(game->snake->direction, key))
        {
            return 1;
        }
        update_snake(game->snake);

        for (size_t i = 1; i < game->snake->length; ++i)
        {
            if (game->snake->body[0]->x == game->snake->body[i]->x
                && game->snake->body[0]->y == game->snake->body[i]->y)
            {
                game->status = GAME_OVER;
                break;
            }
        }

        if (game->snake->body[0]->x == game->apple->x
            && game->snake->body[0]->y == game->apple->y)
        {
            game->score++;
            grow_snake(game->snake);
            spawn_apple(game);
        }
    }

    clear();

    mvprintw(game->apple->y, game->apple->x, APPLE_BODY);

    attron(A_REVERSE);
    for (size_t i = 0; i < game->snake->length; ++i)
    {
        mvprintw(game->snake->body[i]->y, game->snake->body[i]->x, SNAKE_BODY);
    }
    attroff(A_REVERSE);

    return 0;
}

void pause_game(struct Game *game)
{
    char str_score[32];
    snprintf(str_score, sizeof(str_score), "SCORE : %ld", game->score);
    mvprintw(LINES / 3, (COLS / 2) - (strlen(str_score) / 2), "%s", str_score);

    mvprintw(LINES / 2, (COLS / 2) - 2, "PAUSE");
    mvprintw((LINES / 2) + 1, (COLS / 2) - 11, "PRESS \"SPACE\" TO RESUME");
    mvprintw((LINES / 2) + 2, (COLS / 2) - 15,
             "PRESS \"ENTER\" TO RESTART A GAME");
}

void game_over(struct Game *game)
{
    char str_score[32];
    snprintf(str_score, sizeof(str_score), "SCORE : %ld", game->score);
    mvprintw(LINES / 3, (COLS / 2) - (strlen(str_score) / 2), "%s", str_score);

    mvprintw(LINES / 2, (COLS / 2) - 4, "GAME OVER");
    mvprintw((LINES / 2) + 1, (COLS / 2) - 15,
             "PRESS \"ENTER\" TO RESTART A GAME");
}

void spawn_apple(struct Game *game)
{
    int valid_position = 0;

    while (!valid_position)
    {
        game->apple->x = (rand() % (COLS / (int)strlen(SNAKE_BODY)))
            * (int)strlen(SNAKE_BODY);
        game->apple->y = rand() % LINES;

        valid_position = 1;

        for (size_t i = 0; i < game->snake->length; ++i)
        {
            if (game->snake->body[i]->x == game->apple->x
                && game->snake->body[i]->y == game->apple->y)
            {
                valid_position = 0;
                break;
            }
        }
    }
}
