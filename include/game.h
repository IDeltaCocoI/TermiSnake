#ifndef GAME_H
#define GAME_H

#include "snake.h"

struct Game
{
    struct Snake *snake;
    long score;
};

struct Game *new_game();
void free_game(struct Game *game);

#endif
