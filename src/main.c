#define _DEFAULT_SOURCE
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
#include "game.h"

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

    while (1)
    {
        int key = getch();

        if (key == 'q')
        {
            break;
        }

        if (game->status != GAME_OVER && key == ' ')
        {
            game->status = game->status == PLAYING ? PAUSE : PLAYING;
        }

        if (update_game(game, key))
        {
            break;
        }

        if (game->status == PAUSE)
        {
            pause_game(game);
        }

        if (game->status == GAME_OVER)
        {
            game_over(game);
        }

        if ((game->status != PLAYING)
            && (key == 10 || key == 13
                || key == KEY_ENTER)) /* When "Enter" key is press */
        {
            game = new_game(game);
            if (!game)
            {
                endwin();
                return 1;
            }
            game->status = PLAYING;
        }

        refresh();
        usleep(GAME_SPEED);
    }

    free_game(game);

    endwin();
    return 0;
}
