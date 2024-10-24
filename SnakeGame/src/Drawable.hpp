#pragma once

class Drawable
{
public:
    Drawable()
    {
        y = x = 0;
        icon = ' ';
    }

    Drawable(int y, int x, chtype ch)
    {
        this->icon = ch;
        this->x = x;
        this->y = y;
    }

    int getX(){
        return x;
    }
    
    int getY(){
        return y;
    }

    chtype getIcon(){
        return icon;
    }
protected:
    int y, x;
    chtype icon;
};