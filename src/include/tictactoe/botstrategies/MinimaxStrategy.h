#pragma once
#include "tictactoe/botstrategies/IStrategy.h"
#include "tictactoe/Board.h"
#include "tictactoe/VictoryChecker.h"
#include "tictactoe/Move.h"

namespace tictactoe {
namespace botstrategies {

class MinimaxStrategy : public IStrategy {
  public:
    MinimaxStrategy(Board* board, VictoryChecker* victory_checker);
    Move GenerateMove() override;
    ~MinimaxStrategy();
    
  private:
    Board *board_;
    VictoryChecker* victory_checker_;

    static const auto kUserWinScore = -1;
    static const auto kBotWinScore = 1;
    static const auto kTieScore = 0;

    Move Max() const;
    Move Min() const;
};
}
}