#include <stddef.h>
#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "movement.h"
#include "point.h"
#include "snake.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    struct Snake *snake = create_snake(COLS / 2, LINES / 2);
    if (!snake)
    {
        return 1;
    }

    while (1)
    {
        int key = getch();

        if (!move_snake(snake->direction, key))
        {
            break;
        }

        update_snake(snake);

        clear();

        attron(A_REVERSE);
        for (size_t i = 0; i < snake->length; ++i)
        {
            mvprintw(snake->body[i]->y, snake->body[i]->x, SNAKE_BODY);
        }
        attroff(A_REVERSE);

        refresh();

        usleep(100000);
    }

    free_snake(snake);

    endwin();
    return 0;
}
