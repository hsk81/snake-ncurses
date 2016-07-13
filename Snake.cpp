/* 
 * File:   Snake.cpp
 * Author: hsk81
 * 
 * Created on July 12, 2016, 11:48 PM
 */

#include <ncurses.h>

#include "Direction.h"
#include "Snake.h"
#include "SnakeNode.h"
#include "Food.h"

Snake::Snake(int x, int y, int size, Direction dir) {
    this->head = new SnakeNode(x, y);
    SnakeNode *prev = this->head;

    for (int i=0; i<size-1; i++) {
        prev->next = new SnakeNode(--x, y);
        prev = prev->next;
    }
    
    this->direction = dir;
}

Snake::~Snake() {
    while(this->head) {
        SnakeNode *head = this->head;
        SnakeNode *next = head->next;
        this->head = next;
        delete head;
    }
}

Direction Snake::get_direction() const {
    return this->direction;
}

SnakeNode* Snake::get_node(const int index) const {
    SnakeNode *node = this->head;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}

int Snake::get_size() const {
    SnakeNode *node = this->head;
    int size = 0;

    while (node) {
        node = node->next;
        size++;
    }
    return size;
}

bool Snake::is_bitten() const {
    SnakeNode *head = this->head;
    SnakeNode *node = head->next;

    while (node) {
        if (head->x == node->x && head->y == node->y) {
            return true;
        }
        node = node->next;
    }
    return false;
}

bool Snake::is_fed(const Food *food) const {
    SnakeNode *node = this->head;

    while (node && food) {
        if (food->at(node)) {
            return true;
        }
        node = node->next;
    }
    return false;
}

bool Snake::consume(Food *food) const {
    if (this->is_fed(food)) {
        food->setEaten(true);
    }
    return food->getEaten();
}

void Snake::grow() {
    int size = this->get_size();
    SnakeNode *tail = this->get_node(size - 1);
    tail->next = new SnakeNode(tail->x, tail->y);
}

void Snake::move(const Direction dir) {
    this->direction = dir;
    this->move_body();
    this->move_head();
}

void Snake::move_body() {
    SnakeNode *node_lhs = 0;
    SnakeNode *node_rhs = 0;

    int size = this->get_size();
    node_lhs = this->get_node(size - 1);
    mvaddch(node_lhs->y, node_lhs->x, ' ');

    for (int i = size - 1; i > 0; i--) {
        node_lhs = this->get_node(i);
        node_rhs = this->get_node(i - 1);
        node_lhs->x = node_rhs->x;
        node_lhs->y = node_rhs->y;
    }
}

void Snake::move_head() {
    SnakeNode *head = this->head;

    int row, col;
    getmaxyx(stdscr, row, col);

    if (this->direction == RIGHT) {
        head->x = head->x + 1;
        if (head->x > col - 1) {
            head->x = 0;
        }
        return;
    }
    if (this->direction == LEFT) {
        head->x = head->x - 1;
        if (head->x < 0) {
            head->x = col - 1;
        }
        return;
    }
    if (this->direction == DOWN) {
        head->y = head->y - 1;
        if (head->y < 0) {
            head->y = row - 1;
        }
        return;
    }
    if (this->direction == UP) {
        head->y = head->y + 1;
        if (head->y > row - 1) {
            head->y = 0;
        }
        return;
    }
}

void Snake::paint() const {
    SnakeNode *node = this->head;

    attron(COLOR_PAIR(1));
    while (node) {
        mvaddch(node->y, node->x, ' ');
        node = node->next;
    }
    attroff(COLOR_PAIR(1));
}
