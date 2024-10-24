#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include <queue>

enum direction{
    up = -1,
    down = 1,
    left = -2,
    right = 2
};

class SnakePiece : public Drawable
{
public:
    SnakePiece()
    {
        this->y = this->x = 0;
        this->icon = '#';
    }

    SnakePiece(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = '#';
    }
};

class Snake
{
    std::queue<SnakePiece> prev_pieces;
    direction cur_direction;
public:
    Snake(){
        cur_direction = down;
    }

    void addPiece(SnakePiece piece){
        prev_pieces.push(piece);
    }

    void removePiece(){
        prev_pieces.pop();
    }

    SnakePiece tail(){
        return prev_pieces.front();
    }

    SnakePiece head(){
        return prev_pieces.back();
    }

    direction getDirection(){
        return cur_direction;
    }

    void setDirection(direction new_dir){
        if (cur_direction + new_dir != 0){
            cur_direction = new_dir;
        }
    }

    SnakePiece nextHead(){
        int row = head().getY();
        int col = head().getX();

        switch(cur_direction){
            case up:
                row--;
                break;
            case down:
                row++;
                break;
            case left:
                col--;
                break;
            case right:
                col++;
                break;
        }

        return SnakePiece(row, col);
    }
};