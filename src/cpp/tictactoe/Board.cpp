#include "tictactoe/Board.h"
#include <iostream>
#include <unistd.h>

using namespace tictactoe;

int Board::GetCell(int x, int y) const {
  return game_board_[y][x];
}

void Board::SetCell(int x, int y, int player) {
  game_board_[y][x] = player;
}

void Board::SetUserChar(char c) {
  user_char_ = c;
}

void Board::SetBotChar(char c) {
  bot_char_ = c;
}

void Board::ResetBoard() {
  for(int i = 0; i < kRowAndCollSize; ++i)
    for(int j = 0; j < kRowAndCollSize; ++j) {
      game_board_[i][j] = 0;
    }
}

char Board::GetUserChar() const {
  return user_char_;
}

char Board::GetBotChar() const {
  return bot_char_;
}