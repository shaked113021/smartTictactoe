#pragma once
#include "tictactoe/botstrategies/Strategy.h"
#include "tictactoe/Board.h"
#include "tictactoe/VictoryChecker.h"

namespace tictactoe {
namespace botstrategies {

  class MinimaxStrategy : Strategy {
    public:
      MinimaxStrategy(Board* board, VictoryChecker* victory_checker);
      virtual void DoMove() override;
    private:
      Board *board_;
      VictoryChecker* victory_checker_;
  };
}
}