#pragma once
#include "Board.h"

namespace tictactoe {
class VictoryChecker {
  public:
    VictoryChecker(Board* board);
    int Check();
  private:
    Board* board_;
    int CheckDiagonals();
    int CheckRows();
    int CheckCols();
};
};