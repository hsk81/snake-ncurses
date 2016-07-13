
/* 
 * File:   SnakeNode.h
 * Author: hsk81
 *
 * Created on July 13, 2016, 1:16 AM
 */

#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

class Snake;

class SnakeNode {
    friend Snake;
private:
    SnakeNode *next;
    int x;
    int y;

public:
    SnakeNode(int x, int y, SnakeNode* next = 0);
    virtual ~SnakeNode();
    
public:
    bool at(const int x, const int y) const;
};

#endif /* SNAKE_NODE_H */

