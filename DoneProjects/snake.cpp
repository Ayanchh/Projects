#include <ncurses.h>
#include "src/SnakeGame.hpp"

int main(){
    initscr();
    refresh();

    noecho();
    curs_set(0);

    SnakeGame game(20, 40, 100);

    while(!game.isOver()){
        game.processInput();
        game.updateState();
        game.redraw();
    }

    game.lose_screen();
    while(getch() != 'q'){
        ;
    }
    endwin();
}