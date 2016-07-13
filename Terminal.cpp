/* 
 * File:   Terminal.cpp
 * Author: hsk81
 * 
 * Created on July 13, 2016, 3:56 AM
 */

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "Terminal.h"

Terminal::Terminal() {
    srand(time(NULL));

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    noecho();

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
}

Terminal::~Terminal() {
    endwin();
}

Direction Terminal::control(const Direction dir) const {
    switch (getch()) {
        case KEY_RIGHT:
            if (dir != LEFT) return RIGHT;
            break;

        case KEY_LEFT:
            if (dir != RIGHT) return LEFT;
            break;

        case KEY_UP:
            if (dir != UP) return DOWN;
            break;

        case KEY_DOWN:
            if (dir != DOWN) return UP;
            break;

        default:
            return dir;
    }
    return dir;
}

void Terminal::sleep(const int ms) const {
    struct timespec *ts = new timespec;
    ts->tv_sec = 0;
    ts->tv_nsec = 1E6 * ms;
    nanosleep(ts, NULL);
    delete ts;
}

void Terminal::paint() const {
    refresh();
}
