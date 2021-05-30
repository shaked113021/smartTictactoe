#pragma once
#include "tictactoe/botstrategies/Strategy.h"
#include "tictactoe/Board.h"

namespace tictactoe {
namespace botstrategies {

  class RandomStrategy : Strategy {
    public:
      RandomStrategy(Board* board);
      virtual void DoMove() override;
    private:
      Board *board_;
  };
}
}