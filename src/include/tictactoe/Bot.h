#pragma once
#include "Board.h"
#include "VictoryChecker.h"
#include "botstrategies/IStrategy.h"

namespace tictactoe {
class Bot {
  public:
    Bot(Board* board, botstrategies::IStrategy* strategy);
    void DoMove() const;
  private:
    Board* board_;
    botstrategies::IStrategy* strategy_;
};
};
