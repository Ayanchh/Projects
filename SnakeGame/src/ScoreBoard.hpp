#pragma once
#include <ncurses.h>
#include <vector>
#include <string>

class ScoreBoard
{
    WINDOW * score_win;
    int score;
public:
    ScoreBoard(){
        score_win = newwin(1, 30, 10, 10);
    }

    ScoreBoard(int width, int y, int x){
        score_win = newwin(1, width, y, x);
    }

    void setup(){
        clear();
        refresh();
        mvwprintw(score_win, 0, 1, "Score:");
        score = 0;
        updateScore();
    }

    void clear(){
        wclear(score_win);
    }

    int getScore(){
        return score;
    }

    void scoreUp(){
        score+=100;
        refresh();
    }

    void updateScore(){
        mvwprintw(score_win, 0, 27, "%10llu", score);
        refresh();
    }
    
    void refresh(){
        wrefresh(score_win);
    }
};