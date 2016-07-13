/* 
 * File:   SnakeNode.cpp
 * Author: hsk81
 * 
 * Created on July 13, 2016, 1:16 AM
 */

#include "SnakeNode.h"

SnakeNode::SnakeNode(int x, int y, SnakeNode* next) {
    this->next = next;
    this->x = x;
    this->y = y;
}

SnakeNode::~SnakeNode() {
}

bool SnakeNode::at(const int x, const int y) const {
    return this->x == x && this->y == y;
};
