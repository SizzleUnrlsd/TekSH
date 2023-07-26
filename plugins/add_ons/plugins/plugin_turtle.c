#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/shell.h"

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

#define MAX_TURTLES 10

typedef struct {
    int x;
    int y;
    int direction;
} Turtle;

void draw_turtle1_right(Turtle t)
{
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y, t.x, "  ");
    attron(COLOR_PAIR(1));
    printw("_____");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("     ____");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 1, t.x, "");
    attron(COLOR_PAIR(1));
    printw(" /      \\");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("  |  o |");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 2, t.x, "");
    attron(COLOR_PAIR(1));
    printw("|        |");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("/ ___\\|");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 3, t.x, "");
    attron(COLOR_PAIR(1));
    printw("|_________/");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("      ");
    attroff(COLOR_PAIR(1));
    mvprintw(t.y + 4, t.x, "|_| | |_| |");
}

void draw_turtle2_right(Turtle t)
{
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y, t.x, "  ");
    attron(COLOR_PAIR(1));
    printw("_____");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("     ____");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 1, t.x, "");
    attron(COLOR_PAIR(1));
    printw(" /      \\");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("  |  o |");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 2, t.x, "");
    attron(COLOR_PAIR(1));
    printw("|        |");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("/ ___\\|");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 3, t.x, "");
    attron(COLOR_PAIR(1));
    printw("|_________/");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("      ");
    attroff(COLOR_PAIR(1));
    mvprintw(t.y + 4, t.x, "| |_| | |_|");
}

void draw_turtle1_left(Turtle t)
{
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y, t.x, "  ");
    attron(COLOR_PAIR(1));
    printw("_____");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("     ____");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 1, t.x, "");
    attron(COLOR_PAIR(1));
    printw("  |  o |");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw(" /      \\");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 2, t.x, "");
    attron(COLOR_PAIR(1));
    printw("/ ___\\|");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("|        |");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 3, t.x, "");
    attron(COLOR_PAIR(1));
    printw("      ");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("|_________/");
    attroff(COLOR_PAIR(1));
    mvprintw(t.y + 4, t.x, "|_| | |_| |");
}

void draw_turtle2_left(Turtle t)
{
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y, t.x, "  ");
    attron(COLOR_PAIR(1));
    printw("_____");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("     ____");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 1, t.x, "");
    attron(COLOR_PAIR(1));
    printw("  |  o |");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw(" /      \\");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 2, t.x, "");
    attron(COLOR_PAIR(1));
    printw("/ ___\\|");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("|        |");

    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(t.y + 3, t.x, "");
    attron(COLOR_PAIR(1));
    printw("      ");
    attroff(COLOR_PAIR(1) | A_BOLD);
    printw("|_________/");
    attroff(COLOR_PAIR(1));
    mvprintw(t.y + 4, t.x, "| |_| | |_|");
}


void erase_turtle(Turtle t)
{
    mvprintw(t.y, t.x, "                 ");
    mvprintw(t.y + 1, t.x, "                 ");
    mvprintw(t.y + 2, t.x, "                 ");
    mvprintw(t.y + 3, t.x, "                 ");
    mvprintw(t.y + 4, t.x, "                ");
}


void move_turtle(Turtle *t, int dx, int dy, int *toggle)
{
    erase_turtle(*t);
    t->x += dx;
    t->y += dy;
    
    if (dx < 0) {
        t->direction = 1;
    } else if (dx > 0) {
        t->direction = 0;
    }

    if (t->direction == 0) {
        if (*toggle) {
            draw_turtle1_right(*t);
        } else {
            draw_turtle2_right(*t);
        }
    } else {
        if (*toggle) {
            draw_turtle1_left(*t);
        } else {
            draw_turtle2_left(*t);
        }
    }
    
    *toggle = !(*toggle);
}

void cleanup(void)
{
    system("pkill aplay");
    wait(NULL);
}


int turtle(void)
{
    Turtle turtles[MAX_TURTLES];
    int num_turtles = 1;
    int i;
    int toggle = 0;

    initscr();
    start_color();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    turtles[0].x = 0;
    turtles[0].y = 0;
    turtles[0].direction = 0;

    system("aplay turtle.wav >/dev/null 2>&1 &");

    atexit(cleanup);

    while (num_turtles > 0) {
        int key = getch();
        switch (key) {
            case KEY_LEFT:
                move_turtle(&turtles[0], -1, 0, &toggle);
                break;
            case KEY_RIGHT:
                move_turtle(&turtles[0], 1, 0, &toggle);
                break;
            case KEY_UP:
                move_turtle(&turtles[0], 0, -1, &toggle);
                break;
            case KEY_DOWN:
                move_turtle(&turtles[0], 0, 1, &toggle);
                break;
            case 'q':
                num_turtles = 0;
                break;
        }
        if (turtles[0].x >= COLS || turtles[0].x < 0 ||
            turtles[0].y >= LINES || turtles[0].y < 0) {
            num_turtles = 0;
        }
        refresh();
    }
    endwin();
    return 0;
}


int
execution(int argc UNUSED_ARG, char **argv UNUSED_ARG)
{
    turtle();
    return 0;
}

plugin_t *
init(void)
{
    char **env = (char **)malloc(sizeof(char *) * 13);
    plugin_t *plugin = (plugin_t*)malloc(sizeof(plugin_t));

    if (plugin == NULL) {
        exit(EXIT_FAILURE);
    }

    plugin->execute = &execution;
    plugin->command = strdup("turtle");

    return plugin;
}
