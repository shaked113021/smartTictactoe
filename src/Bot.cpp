#include "Headers/Bot.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
void Bot::doMove(Board *board) {
    Move ret = minimax(board, BOT);
    board->setCell(ret.x, ret.y, BOT);
}


Bot::Move Bot::minimax(Board *board, int player) {
    switch(board->checkVictory()) {
        case USER:
            return Move(-1);
        case BOT:
            return Move(1);
        case TIE:
            return Move(0);
            break;
        case 0:
            break;
        default:
            exit(1);
    }

    std::vector<Move> *moves = new std::vector<Move>;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
        {
            if(board->getCell(j, i) == UNUSED) {

                board->setCell(j, i, player);
                Move move(j,i);
                if(player == BOT) {
                    move.score = minimax(board, USER).score;
                } else {
                    move.score = minimax(board, BOT).score;
                }
                moves->push_back(move);
                board->setCell(j, i, UNUSED);
            }
        }
    }

    moves->shrink_to_fit();
    int bestMove = 0;

    if(player == BOT) {
        int bestScore = -1000000;
        for(int i = 0; i < (int)moves->size(); i++) {
            if((*moves)[i].score > bestScore) {
                bestMove = i;
                bestScore = (*moves)[i].score;
            }
        }
    } else {
        int bestScore = 1000000;
        for(int i = 0; i < (int)moves->size(); i++) {
            if((*moves)[i].score < bestScore) {
                bestMove = i;
                bestScore = (*moves)[i].score;
            }
        }
    }
    Move ret = (*moves)[bestMove];
    delete moves;
    return ret;
}

void Bot::doRandom(Board *board){
    int x, y;
    do{
        x = rand() % 2;
        y = rand() % 2;
    } while(board->getCell(x,y) != UNUSED);
    board->setCell(x, y, BOT);
}