/*
 * File:   main.cpp
 * Author: hsk81
 *
 * Created on June 13, 2016, 10:44 AM
 */

#include "main.h"

#include "Direction.h"
#include "Food.h"
#include "Snake.h"
#include "Terminal.h"

int main(int argc, char** argv) {
    Terminal *terminal = new Terminal();
    Snake *snake = new Snake(0, 0, 5);
    Food *food = new Food(0, 0);

    while (!snake->bitten()) {
        food->reset(snake);
        food->paint();
        snake->paint();

        terminal->paint();
        terminal->sleep();
        
        Direction dir = snake->get_direction();
        snake->move(terminal->control(dir));

        if (snake->consume(food)) {
            snake->grow();
        }
    }

    delete food;
    delete snake;
    delete terminal;

    return 0;
}
