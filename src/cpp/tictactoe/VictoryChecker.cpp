#include "tictactoe/VictoryChecker.h"

using namespace tictactoe;
VictoryChecker::VictoryChecker(const Board* t_board) : m_board((Board*)t_board) {}

int VictoryChecker::CheckDiagonals()
{
  // check diagonals
  bool main_diagonal = true, second_diagonal = true;
  if(this->m_board->GetCell(0, 0) == kUnused) main_diagonal = false;
  if(this->m_board->GetCell(2, 0) == kUnused) second_diagonal = false;

  for(int i = 0; i < kRowAndCollSize - 1; ++i)
  {
    if(main_diagonal&& this->m_board->GetCell(i, i) != this->m_board->GetCell(i+1, i+1))
      main_diagonal = false;
    if(second_diagonal && m_board->GetCell(2-i, i) != this->m_board->GetCell(2-(i+1), i+1))
      second_diagonal = false;
  }
  if(main_diagonal) return this->m_board->GetCell(0, 0);
  if(second_diagonal) return this->m_board->GetCell(2, 0);
  
  return kGamePending;
}

int VictoryChecker::CheckRows()
{
  // check rows 
  for(int i = 0; i < kRowAndCollSize; ++i)
  {
    if(this->m_board->GetCell(0, i) == kUnused) continue;
    bool check_row = true;
    for(int j = 1; j < kRowAndCollSize; ++j)
    {
      if(check_row && this->m_board->GetCell(j, i) != this->m_board->GetCell(j-1, i))
        check_row = false;
    }
    if(check_row) return this->m_board->GetCell(0, i);
  }
  return kGamePending;
}

int VictoryChecker::CheckCols()
{
  // check cols
  for(int j = 0; j < kRowAndCollSize; ++j)
  {
    bool check_col = true;
    if(this->m_board->GetCell(j, 0) == kUnused) check_col = false;
    for(int i = 0; i < kRowAndCollSize - 1; ++i)
    {
      if(check_col && this->m_board->GetCell(j, i) != this->m_board->GetCell(j, i+1))
        check_col = false;
    }
    if(check_col) return this->m_board->GetCell(j, 0);
  }
  return kGamePending;
}

int VictoryChecker::Check()
{
  // declarations
  int check_result;

  if ((check_result = this->CheckDiagonals()) != kGamePending)
  {
    return check_result;
  }

  if ((check_result = this->CheckRows()) != kGamePending)
  {
    return check_result;
  }

  if ((check_result = this->CheckCols()) != kGamePending)
  {
    return check_result;
  }
  
  // if any cells are empty, return game pending
  for(int i = 0; i < kRowAndCollSize; ++i)
  {
    for(int j = 0; j < kRowAndCollSize; ++j)
    {
      if(this->m_board->GetCell(j, i) == kUnused)
        return kGamePending;
    }
  }

  // if no other option left, this is a tie
  return kTie;
}