/* 
 * File:   Terminal.h
 * Author: hsk81
 *
 * Created on July 13, 2016, 3:56 AM
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include "Direction.h"

class Terminal {
public:
    Terminal();
    virtual ~Terminal();

public:
    Direction control(const Direction dir) const;
    void sleep(const int ms = 25) const;

public:
    void paint() const;
};

#endif /* TERMINAL_H */
