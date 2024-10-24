#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include "Empty.hpp"
#include "Fruit.hpp"
#include "Snake.hpp"

class Board
{
public:
    Board(){
        construct(0, 0, 10);
    }

    Board(int height, int width, int speed){
        construct(height, width, speed);
    }

    void setup(){
        clear();
        refresh();
    }

    void add(Drawable drawable){
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch){
        mvwaddch(board_win, y, x, ch);
    }

    void getEmptyCoordinates(int& y, int& x){
        while((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ')
            ;
    }

    chtype getInput(){
        halfdelay(5);
        return wgetch(board_win);
    }
    
    void addBox(){
        box(board_win, 0, 0);
    }

    void clear(){
        wclear(board_win);
        addBox();
    }
    
    void refresh(){
        wrefresh(board_win);
    }
    
    chtype getCharAt(int y, int x){
        return mvwinch(board_win, y, x);
    }

    void setTimeout(int timeout){
        wtimeout(board_win, timeout);
    }
    
    void board_lose(int score){
        clear();
        mvwprintw(board_win, 9, 15, "You Lose!");
    }

    int getStartRow(){
        return StartRow;
    }

    int getStartCol(){
        return StartCol;
    }

    int getTimeout(){
        return timeout;
    }
private:
    WINDOW * board_win;
    int timeout, height, width, StartRow, StartCol;
    void construct(int height, int width, int speed){
        int xMax, yMax;
        getmaxyx(stdscr, yMax, xMax);
        this->height = height;
        this->width = width;
        StartRow = (yMax/2) - (height / 2);
        StartCol = (xMax/2) - (width / 2);
        board_win = newwin(height, width, StartRow, StartCol);

        timeout = speed;
        setTimeout(speed);
        keypad(board_win, true);
    }
};