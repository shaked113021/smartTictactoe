#pragma once
#include "Board.h"
class Bot {
    public:
        void doMove(Board *board);
        void setIsFirst(bool);
    private:
        struct Move {
            int x;
            int y;
            int score;
            Move(int mx, int my){x = mx, y= my;};
            Move(int scr) {score = scr;};
        };
        
        Move minimax(Board *board, int player);
        void doRandom(Board *board);
        bool isFirst = true;
    
};