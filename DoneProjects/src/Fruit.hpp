#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Fruit : public Drawable
{
public:
    Fruit(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = 'F';
    }
};