/*
 * File:   main.cpp
 * Author: hsk81
 *
 * Created on June 13, 2016, 10:44 AM
 */

#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "main.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {

    srand(time(NULL));

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);

    int gamespeed = 25; // milli seconds
    int direction = DIR_RIGHT;

    struct SnakeNode *snake = NULL;
    snake_create(&snake);
    struct Food food;
    food.eaten = 1;

    do {
        food_create(&food, snake);
        paint(snake, food);
        sleep(gamespeed);
        refresh();
    } while (simulate(&snake, &direction, &food));

    snake_destroy(&snake);
    endwin();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void paint(struct SnakeNode *snake, struct Food food) {
    struct SnakeNode *node = snake;

    attron(COLOR_PAIR(1));
    while (node != NULL) {
        mvaddch(node->y, node->x, ' ');
        node = node->next;
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2)|A_BOLD);
    mvaddch(food.y, food.x, '#');
    attroff(COLOR_PAIR(2)|A_BOLD);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int simulate(struct SnakeNode **snake, int *direction, struct Food *food) {

    switch(getch()) {
        case KEY_RIGHT:
            if (*direction != DIR_LEFT) *direction = DIR_RIGHT;
            break;
        case KEY_LEFT:
            if (*direction != DIR_RIGHT) *direction = DIR_LEFT;
            break;
        case KEY_UP:
            if (*direction != DIR_UP) *direction = DIR_DOWN;
            break;
        case KEY_DOWN:
            if (*direction != DIR_DOWN) *direction = DIR_UP;
            break;
        default:
            break;
    }

    snake_move(snake);
    snake_teleport(snake, direction);

    int game_over = !snake_bitten(*snake);
    if (game_over) {
        paint(*snake, *food);
        sleep(2000);
    }

    int food_eaten = (*snake)->x == (*food).x && (*snake)->y == (*food).y;
    if (food_eaten) {
        (*food).eaten = 1;
        snake_grow(snake);
    }

    return game_over;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void food_create(struct Food *food, struct SnakeNode *snake) {

    int row, col;
    getmaxyx(stdscr, row, col);

    if (food->eaten) do {
        food->x = 0.90 * (rand() % col) + 0.05 * col;
        food->y = 0.90 * (rand() % row) + 0.05 * row;
    } while (snake_fed(snake, food));

    food->eaten = 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void snake_create(struct SnakeNode **snake) {
    struct SnakeNode *hnext = NULL;
    struct SnakeNode *hprev = NULL;

    int x = 27;
    int y = 10;
    int size = 0;

    *snake = (struct SnakeNode *) malloc(sizeof (struct SnakeNode));

    (*snake)->x = x;
    (*snake)->y = y;
    (*snake)->next = NULL;

    hprev = *snake;
    hnext = (*snake)->next;

    while (hnext != NULL || size < 4) {
        hnext = (struct SnakeNode *) malloc(sizeof (struct SnakeNode));
        hnext->x = --x;
        hnext->y = y;
        hnext->next = NULL;

        hprev->next = hnext;
        hprev = hnext;
        hnext = hnext->next;

        size++;
    }
}

struct SnakeNode *snake_node(struct SnakeNode *snake, int index) {
    struct SnakeNode *node = snake;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}

int snake_size(struct SnakeNode *snake) {
    int size = 0;

    while (snake != NULL) {
        snake = snake->next;
        size++;
    }
    return size;
}

int snake_bitten(struct SnakeNode *snake) {
    struct SnakeNode *node = snake->next;

    while (node != NULL) {
        if (snake->x == node->x && snake->y == node->y) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

int snake_fed(struct SnakeNode *snake, struct Food *food) {
    struct SnakeNode *node = snake;

    while (node != NULL && food != NULL) {
        if (node->x == food->x && node->y == food->y) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void snake_move(SnakeNode** snake) {
    struct SnakeNode *node_lhs = NULL;
    struct SnakeNode *node_rhs = NULL;

    int size = snake_size(*snake);
    node_lhs = snake_node(*snake, size - 1);
    mvaddch(node_lhs->y, node_lhs->x, ' ');

    for (int i = size - 1; i > 0; i--) {
        node_lhs = snake_node(*snake, i);
        node_rhs = snake_node(*snake, i - 1);
        node_lhs->x = node_rhs->x;
        node_lhs->y = node_rhs->y;
    }
}

void snake_teleport(SnakeNode** snake, int* direction) {

    int row, col;
    getmaxyx(stdscr, row, col);

    if (*direction == DIR_RIGHT) {
        (*snake)->x = (*snake)->x + 1;
        if ((*snake)->x > col - 1) {
            (*snake)->x = 0;
        }
    } else if (*direction == DIR_LEFT) {
        (*snake)->x = (*snake)->x - 1;
        if ((*snake)->x < 0) {
            (*snake)->x = col - 1;
        }
    } else if (*direction == DIR_DOWN) {
        (*snake)->y = (*snake)->y - 1;
        if ((*snake)->y < 0) {
            (*snake)->y = row - 1;
        }
    } else { //DIR_UP?
        (*snake)->y = (*snake)->y + 1;
        if ((*snake)->y > row - 1) {
            (*snake)->y = 0;
        }
    }
}

void snake_grow(SnakeNode** snake) {
    struct SnakeNode *tail_old = NULL;
    struct SnakeNode *tail_new = NULL;

    tail_old = snake_node(*snake, snake_size(*snake) - 1);
    tail_new = (struct SnakeNode *) malloc(sizeof (struct SnakeNode));
    tail_new->x = tail_old->x;
    tail_new->y = tail_old->y;
    tail_new->next = NULL;
    tail_old->next = tail_new;
}

void snake_destroy(struct SnakeNode **snake) {
    struct SnakeNode *node = NULL;

    while (*snake != NULL) {
        node = *snake;
        *snake = (*snake)->next;
        free(node);
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void sleep(int ms) {
    struct timespec *ts = (struct timespec *)malloc(sizeof(struct timespec));
    ts->tv_sec = 0;
    ts->tv_nsec = 1E6*ms;
    nanosleep(ts, NULL);
    free(ts);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
