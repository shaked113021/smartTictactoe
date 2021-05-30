#pragma once
#include "tictactoe/botstrategies/IStrategy.h"
#include "tictactoe/Board.h"
#include "tictactoe/Move.h"

namespace tictactoe {
namespace botstrategies {

class RandomMoveStrategy : public IStrategy {
  public:
    RandomMoveStrategy(Board* t_board);
    Move GenerateMove() override;
    ~RandomMoveStrategy();

  private:
    Board *m_board;
};
}
}