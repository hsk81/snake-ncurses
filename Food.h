/* 
 * File:   Food.h
 * Author: hsk81
 *
 * Created on July 13, 2016, 12:13 AM
 */

#ifndef FOOD_H
#define FOOD_H

class Snake;
class SnakeNode;

class Food {
private:
    int x;
    int y;

public:
    Food(int x = 0, int y = 0);
    virtual ~Food();

public:
    bool at(const SnakeNode* node) const;
    void reset(const Snake* snake);
    void paint() const;
    
private:
    bool is_eaten;
public:
    bool getEaten() const;
    void setEaten(bool is_eaten);
};

#endif /* FOOD_H */

