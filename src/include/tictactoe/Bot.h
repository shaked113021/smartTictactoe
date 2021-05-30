#pragma once
#include "Board.h"
#include "VictoryChecker.h"
#include "botstrategies/IStrategy.h"

namespace tictactoe
{
class Bot
{
  public:
    Bot(Board* t_board, botstrategies::IStrategy* t_strategy);
    void DoMove() const;
  private:
    Board* m_board;
    botstrategies::IStrategy* m_strategy;
};
};
