#include "Headers/Bot.h"
#include <iostream>
#include <unistd.h>
// victory checker 
/*
 *   USER = 1, BOT = 2 ,FALSE = 0, TIE = 3
 */
int Board::checkVictory() {
    bool mainD = true, secondD = true;
    if(gBoard[0][0] == UNUSED) mainD = false;
    if(gBoard[0][2] == UNUSED) secondD = false;
    for(int i = 0; i < 2; i++) {
        if(mainD&& gBoard[i][i] != gBoard[i+1][i+1])
            mainD = false;
        if(secondD&&gBoard[i][2-i] != gBoard[i+1][2-(i+1)])
            secondD = false;
    }
    if(mainD) return gBoard[0][0];
    if(secondD) return gBoard[0][2];

    // check rows 
    for(int i = 0; i < 3; i++) {
        if(gBoard[i][0] == UNUSED) continue;
        bool checkRow = true;
        for(int j = 1; j < 3; j++) {
            if(checkRow&&gBoard[i][j] != gBoard[i][j-1])
                checkRow = false;
        }
        if(checkRow) return gBoard[i][0];
    }

    // check cols
    for(int j = 0; j < 3; j++) {
        bool checkCol = true;
        if(gBoard[0][j] == UNUSED) checkCol = false;
        for(int i = 0; i < 2; i++) {
            if(checkCol && gBoard[i][j] != gBoard[i+1][j])
                checkCol = false;
        }
        if(checkCol) return gBoard[0][j];
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(gBoard[i][j] == UNUSED)
                return 0;
        }
    }

    return TIE;
    
}

int Board::getCell(int x, int y) {
    return gBoard[y][x];
}

void Board::setCell(int x, int y, int player) {
    gBoard[y][x] = player;
}

void Board::drawBoard() {
    int ret = system("clear");
    if(ret != 0) exit(1);
    for(int i = 0; i < 3; i++) {
        printf("|\t");
        for(int j = 0; j < 3; j++)
        {
            switch(gBoard[i][j])
            {
                case USER:
                    printf("%c \t|\t", userChar);
                    break;
                case BOT:
                    printf("%c \t|\t", botChar);
                    break;
                case UNUSED:
                    printf("  \t|\t");
                    break;
                case CURSOR:
                    printf("[] \t|\t");
                    break;
            }
        }
        if(i != 2)printf("\n--------------------------------------------------");
        printf("\n");
    }

    printf("\n");
}

void Board::setUserChar(char c) {
    userChar = c;
}

void Board::setBotChar(char c) {
    botChar = c;
}

void Board::resetBoard() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++) {
            gBoard[i][j] = 0;
        }
}

char Board::getUserChar()
{
    return userChar;
}

char Board::getBotChar()
{
    return botChar;
}