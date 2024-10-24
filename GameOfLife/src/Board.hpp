#pragma once
#include <iostream>
#include <chrono>
#include <thread>

constexpr int square_size = 20;
constexpr int yMax = square_size;
constexpr int xMax = square_size * 5 / 2;

class Board
{
private:
    bool cells[yMax][xMax] = {{0}};
    int frame;
public:
    Board(){
        setup();
    }

    Board(int n){
        setup();
    }

    void setup(){
        cells[10][10] = 1;
        cells[10][11] = 1;
        cells[10][9] = 1;
        cells[11][11] = 1;
        cells[12][10] = 1;
        frame = 1;
    }

    void screenClear(){
        system("clear");
    }
    
    void wait(){
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(50ms); 
    }

    int count_near(int y, int x){
        int cnt = 0;
        for (int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if (j!=0 || i != 0){
                    if (y + i < yMax && y + i >= 0 && x+j < xMax && x+j >= 0){
                        if (cells[y+i][x+j] == 1){
                            cnt++;
                        }
                    }
                }
            }
        }
        return cnt;
    }

    void output(int y, int x){
        if (cells[y][x] == 1){
            std::cout<<'*';
        }else{
            std::cout<<'.';
        }
    }

    void new_frame(){
        std::vector<int> changes;
        screenClear();
        for(int i = 0;  i < yMax; i++){
            for (int j = 0; j < xMax; j++){
                output(i, j);
                int cnt = count_near(i, j);
                if (cells[i][j] == 1){
                    if (cnt < 2){
                        changes.push_back(i);
                        changes.push_back(j);
                        changes.push_back(0);
                    }else if (cnt > 3){
                        changes.push_back(i);
                        changes.push_back(j);
                        changes.push_back(0);
                    }
                }else{
                    if (cnt == 3){
                        changes.push_back(i);
                        changes.push_back(j);
                        changes.push_back(1);
                    }
                }
            }
            std::cout<<'\n';
        }
        for (int i = 0; i < changes.size(); i+=3){
            if (changes[i+2] == 0){
                cells[changes[i]][changes[i+1]] = 0;
            }else{
                cells[changes[i]][changes[i+1]] = 1;
            }
        }
        std::cout<<frame<<std::endl;
        frame++;
        wait();
        changes.clear();
    }
};