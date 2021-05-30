#include "tictactoe/Bot.h"
#include "tictactoe/Move.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <memory>

using namespace tictactoe;
using namespace botstrategies;

// getting board and victory checker in constractor
Bot::Bot(Board* t_board, IStrategy* t_strategy) : m_board(t_board), m_strategy(t_strategy) {}

void Bot::DoMove() const
{
  // Using strategy to generate move
  Move next_move = this->m_strategy->GenerateMove();
  m_board->SetCell(next_move.x, next_move.y, kBot);
  
}
