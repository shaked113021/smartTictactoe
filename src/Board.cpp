#include "Headers/Bot.h"
#include <iostream>
#include <unistd.h>

using namespace tictactoe;
// victory checker 
/*
 *   kUser = 1, kBot = 2 ,FALSE = 0 kTIE = 3
 */
int Board::CheckVictory() {
  // check diagonals
  bool main_diagonal = true, second_diagonal = true;
  if(game_board_[0][0] == kUnused) main_diagonal = false;
  if(game_board_[0][2] == kUnused) second_diagonal = false;
  for(int i = 0; i < 2; ++i) {
    if(main_diagonal&& game_board_[i][i] != game_board_[i+1][i+1])
      main_diagonal = false;
    if(second_diagonal&&game_board_[i][2-i] != game_board_[i+1][2-(i+1)])
      second_diagonal = false;
  }
  if(main_diagonal) return game_board_[0][0];
  if(second_diagonal) return game_board_[0][2];

  // check rows 
  for(int i = 0; i < 3; ++i) {
    if(game_board_[i][0] == kUnused) continue;
    bool check_row = true;
    for(int j = 1; j < 3; ++j) {
      if(check_row&&game_board_[i][j] != game_board_[i][j-1])
        check_row = false;
    }
    if(check_row) return game_board_[i][0];
  }

  // check cols
  for(int j = 0; j < 3; ++j) {
    bool check_col = true;
    if(game_board_[0][j] == kUnused) check_col = false;
    for(int i = 0; i < 2; ++i) {
      if(check_col && game_board_[i][j] != game_board_[i+1][j])
        check_col = false;
    }
    if(check_col) return game_board_[0][j];
  }

  // if all empty, return false
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 3; ++j) {
      if(game_board_[i][j] == kUnused)
        return 0;
    }
  }

  // if no other option left, this is a tie
  return kTie;
    
}

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
  for(int i = 0; i < 3; ++i)
    for(int j = 0; j < 3; ++j) {
      game_board_[i][j] = 0;
    }
}

char Board::GetUserChar() const {
  return user_char_;
}

char Board::GetBotChar() const {
  return bot_char_;
}