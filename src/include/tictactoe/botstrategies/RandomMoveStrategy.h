#pragma once
#include "tictactoe/botstrategies/IStrategy.h"
#include "tictactoe/Board.h"
#include "tictactoe/Move.h"

namespace tictactoe {
namespace botstrategies {

class RandomMoveStrategy : public IStrategy {
  public:
    RandomMoveStrategy(Board* board);
    Move GenerateMove() override;
    ~RandomMoveStrategy();

  private:
    Board *board_;
};
}
}