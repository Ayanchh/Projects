#include <raylib.h>
#include "src/Board.hpp"

int main(){
    Board board(1);

    while(true){
        board.new_frame();
    }
}