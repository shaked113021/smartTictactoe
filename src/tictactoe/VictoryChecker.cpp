#include "../Headers/tictactoe/VictoryChecker.h"

using namespace tictactoe;
VictoryChecker::VictoryChecker(Board* board) : board_(board) {}

int VictoryChecker::Check() {
  // check diagonals
  bool main_diagonal = true, second_diagonal = true;
  if(this->board_->GetCell(0, 0) == kUnused) main_diagonal = false;
  if(this->board_->GetCell(2, 0) == kUnused) second_diagonal = false;

  for(int i = 0; i < kRowAndCollSize - 1; ++i) {
    if(main_diagonal&& this->board_->GetCell(i, i) != this->board_->GetCell(i+1, i+1))
      main_diagonal = false;
    if(second_diagonal && board_->GetCell(2-i, i) != this->board_->GetCell(2-(i+1), i+1))
      second_diagonal = false;
  }
  if(main_diagonal) return this->board_->GetCell(0, 0);
  if(second_diagonal) return this->board_->GetCell(2, 0);

  // check rows 
  for(int i = 0; i < kRowAndCollSize; ++i) {
    if(this->board_->GetCell(0, i) == kUnused) continue;
    bool check_row = true;
    for(int j = 1; j < kRowAndCollSize; ++j) {
      if(check_row && this->board_->GetCell(j, i) != this->board_->GetCell(j-1, i))
        check_row = false;
    }
    if(check_row) return this->board_->GetCell(0, i);
  }

  // check cols
  for(int j = 0; j < kRowAndCollSize; ++j) {
    bool check_col = true;
    if(this->board_->GetCell(j, 0) == kUnused) check_col = false;
    for(int i = 0; i < kRowAndCollSize - 1; ++i) {
      if(check_col && this->board_->GetCell(j, i) != this->board_->GetCell(j, i+1))
        check_col = false;
    }
    if(check_col) return this->board_->GetCell(j, 0);
  }

  // if all empty, return false
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 3; ++j) {
      if(this->board_->GetCell(j, i) == kUnused)
        return 0;
    }
  }

  // if no other option left, this is a tie
  return kTie;
}