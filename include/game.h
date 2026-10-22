#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "snake.h"

enum Status
{
    PLAYING = 0,
    PAUSE = 1,
    GAME_OVER = 2
};

struct Game
{
    enum Status status;
    struct Snake *snake;
    struct Point *apple;
    long score;
};

/* If a game is already running, it give in parameters. The function free
 * old_game and return a new one */
struct Game *new_game(struct Game *old_game);
void free_game(struct Game *game);

int update_game(struct Game *game, int key);

void spawn_apple(struct Game *game);

void pause_game(struct Game *game);
void game_over(struct Game *game);

#endif
