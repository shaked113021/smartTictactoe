#pragma once
#define USER 1
#define BOT 2
#define UNUSED 0
#define TIE 3
#define CURSOR 3

class Board {
    public:
        int checkVictory();
        int getCell(int x, int y);
        void setCell(int x, int y, int player);
        void drawBoard();
        void setUserChar(char c);
        void setBotChar(char c);
        char getUserChar();
        char getBotChar();
        void resetBoard();
    private:
        int gBoard[3][3];
        char userChar, botChar;
};