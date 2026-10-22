#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "game.h"
#include "movement.h"
#include "snake.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));

    struct Game *game = new_game(NULL);
    if (!game)
    {
        endwin();
        return 1;
    }

    struct Snake *snake = game->snake;

    int paused = 0;

    while (1)
    {
        int key = getch();

        if (key == ' ')
        {
            paused = !paused;
        }

        if (!paused)
        {
            if (!move_snake(snake->direction, key))
            {
                break;
            }
            update_snake(snake);

            if (snake->body[0]->x == game->apple->x
                && snake->body[0]->y == game->apple->y)
            {
                grow_snake(snake);
                spawn_apple(game);
            }
        }

        clear();

        mvprintw(game->apple->y, game->apple->x, APPLE_BODY);

        attron(A_REVERSE);
        for (size_t i = 0; i < snake->length; ++i)
        {
            mvprintw(snake->body[i]->y, snake->body[i]->x, SNAKE_BODY);
        }
        attroff(A_REVERSE);

        if (paused)
        {
            int status = pause_game(&game, key);
            if (status == 1 || status == 2)
            {
                break;
            }
            if (status == 3)
            {
                snake = game->snake;
                paused = 0;
            }
        }

        refresh();
        usleep(GAME_SPEED);
    }

    free_game(game);

    endwin();
    return 0;
}
