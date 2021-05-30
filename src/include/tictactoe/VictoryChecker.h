#pragma once
#include "Board.h"

namespace tictactoe
{
class VictoryChecker
{
  public:
    VictoryChecker(Board* t_board);
    int Check();
  private:
    Board* m_board;
    int CheckDiagonals();
    int CheckRows();
    int CheckCols();
};
};