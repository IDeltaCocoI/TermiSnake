#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
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

    struct Game *game = new_game();
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
        }
        else if (key == 'q')
        {
            break;
        }

        clear();

        attron(A_REVERSE);
        for (size_t i = 0; i < snake->length; ++i)
        {
            mvprintw(snake->body[i]->y, snake->body[i]->x, SNAKE_BODY);
        }
        attroff(A_REVERSE);

        if (paused)
        {
            mvprintw(LINES / 2, (COLS / 2) - 3, "PAUSE");
        }

        refresh();
        usleep(100000);
    }

    free_snake(snake);

    endwin();
    return 0;
}
