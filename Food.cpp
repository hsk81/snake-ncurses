/* 
 * File:   Food.cpp
 * Author: hsk81
 * 
 * Created on July 13, 2016, 12:13 AM
 */

#include <ncurses.h>
#include <stdlib.h>

#include "Food.h"
#include "Snake.h"
#include "SnakeNode.h"

Food::Food(int x, int y) {
    this->is_eaten = false;
    this->x = x;
    this->y = y;
}

Food::~Food() {
}

bool Food::at(const SnakeNode* node) const {
    return node->at(this->x, this->y);
}

void Food::reset(const Snake* snake) {

    if (this->is_eaten) {
        this->is_eaten = false;

        int row, col;
        getmaxyx(stdscr, row, col);

        do {
            this->x = 0.90 * (rand() % col) + 0.05 * col;
            this->y = 0.90 * (rand() % row) + 0.05 * row;
        } while (snake->is_fed(this)); //@todo: de-randomize!
    }
}

void Food::paint() const {
    attron(COLOR_PAIR(2) | A_BOLD);
    mvaddch(this->y, this->x, '#');
    attroff(COLOR_PAIR(2) | A_BOLD);
}

bool Food::getEaten() const {
    return this->is_eaten;
}

void Food::setEaten(bool is_eaten) {
    this->is_eaten = is_eaten;
}
