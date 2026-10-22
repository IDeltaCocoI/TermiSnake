#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "snake.h"

struct Game
{
    struct Snake *snake;
    struct Point *apple;
    long score;
};

/* If a game is already running, it give in parameters. The function free
 * old_game and return a new one */
struct Game *new_game(struct Game *old_game);
void free_game(struct Game *game);

int pause_game(struct Game **game, int key);
void spawn_apple(struct Game *game);

#endif
