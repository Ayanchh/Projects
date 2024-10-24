#pragma once
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "Empty.hpp"
#include "Fruit.hpp"
#include "Board.hpp"
#include "ScoreBoard.hpp"
#include "Drawable.hpp"
#include "Snake.hpp"

class SnakeGame
{
    Board board;
    bool gameOver;
    ScoreBoard scoreBoard;
    Fruit *fruit;
    Snake snake;
public:
    SnakeGame(int height, int width, int speed){
        board = Board(height, width, speed);
        int sb_row = board.getStartRow() + height;
        int sb_col = board.getStartCol();
        scoreBoard = ScoreBoard(width, sb_row, sb_col);
        setup();
    }

    ~SnakeGame(){
        delete fruit;
    }

    void setup(){
        fruit = NULL;

        board.setup();
        scoreBoard.setup();
        gameOver = false;
        srand(time(NULL));
        snake.setDirection(down);

        SnakePiece next = SnakePiece(1,1);
        board.add(next);
        snake.addPiece(next);

        next = snake.nextHead();
        board.add(next);
        snake.addPiece(next);

        next = snake.nextHead();
        board.add(next);
        snake.addPiece(next);

        snake.setDirection(right);

        next = snake.nextHead();
        board.add(next);
        snake.addPiece(next);

        if (fruit == NULL){
            int y, x;
            board.getEmptyCoordinates(y, x);
            fruit = new Fruit(y, x);
            board.add(*fruit);
        }        
    }

    void processInput(){
        chtype input = board.getInput();
        int old_timeout = board.getTimeout();
        switch(input){
            case 'w':
            case KEY_UP:
                snake.setDirection(up);
                break;
            case 's':
            case KEY_DOWN:
                snake.setDirection(down);
                break;
            case 'a':
            case KEY_LEFT:
                snake.setDirection(left);
                break;
            case 'd':
            case KEY_RIGHT:
                snake.setDirection(right);
                break;
            case 'p':
            {
                board.setTimeout(-1);
                while(board.getInput() != 'p'){
                    ;
                }
                board.setTimeout(old_timeout);
                break;
            }
            case 'q':
                gameOver = 1;
                break;
            default:
                break;
                            
        }
    }

    void updateState(){
        SnakePiece next = snake.nextHead();

        switch (board.getCharAt(next.getY(), next.getX())){
            case ' ':
            {
                int emptyRow = snake.tail().getY();
                int emptyCol = snake.tail().getX();

                board.add(Empty(emptyRow, emptyCol));
                snake.removePiece();
                break;
            }
            case 'F':
                scoreBoard.scoreUp();
                scoreBoard.updateScore();
                delete fruit;
                fruit = NULL;
                break;
            default:
                gameOver = 1;
                break;
        }
        board.add(next);
        snake.addPiece(next);

        if (fruit == NULL){
            int y, x;
            board.getEmptyCoordinates(y, x);
            fruit = new Fruit(y, x);
            board.add(*fruit);
        }
    }

    void lose_screen(){
        board.board_lose(getScore());
        redraw();
    }

    void redraw(){
        board.refresh();
    }

    bool isOver(){
        return gameOver;
    }

    void setOver(){
        gameOver = 1;
    }
    
    int getScore(){
        return scoreBoard.getScore();
    }
};