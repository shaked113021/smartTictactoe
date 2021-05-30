#pragma once
#include "tictactoe/botstrategies/IStrategy.h"
#include "tictactoe/Board.h"
#include "tictactoe/VictoryChecker.h"
#include "tictactoe/Move.h"

namespace tictactoe
{
namespace botstrategies
{

class MinimaxStrategy : public IStrategy
{
  public:
    MinimaxStrategy(Board* t_board, VictoryChecker* t_victory_checker);
    Move GenerateMove() override;
    ~MinimaxStrategy();
    
  private:
    Board *m_board;
    VictoryChecker* m_victory_checker;

    static const auto kUserWinScore = -1;
    static const auto kBotWinScore = 1;
    static const auto kTieScore = 0;

    Move Max() const;
    Move Min() const;
};
}
}