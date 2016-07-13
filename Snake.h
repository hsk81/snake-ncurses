/* 
 * File:   Snake.h
 * Author: hsk81
 *
 * Created on July 12, 2016, 11:48 PM
 */

#ifndef SNAKE_H
#define SNAKE_H

#include "Direction.h"

class Food;
class SnakeNode;

class Snake {
private:
    Direction direction;
    SnakeNode *head;

public:
    Snake(int x = 0, int y = 0, int size = 2, Direction dir = RIGHT);
    virtual ~Snake();

public:
    Direction get_direction() const;
    SnakeNode* get_node(const int index) const;
    int get_size() const;

public:
    bool is_bitten() const;
    bool is_fed(const Food *food) const;

public:
    bool consume(Food *food) const;
    void grow();

public:
    void move(const Direction dir);
private:
    void move_body();
    void move_head();

public:
    void paint() const;
};

#endif /* SNAKE_H */
