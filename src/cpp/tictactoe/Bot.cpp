#include "tictactoe/Bot.h"
#include "tictactoe/Move.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <memory>

using namespace tictactoe;
using namespace botstrategies;

// getting board and victory checker in constractor
Bot::Bot(const Board* t_board, const IStrategy* t_strategy) : m_board((Board*)t_board), m_strategy((IStrategy*)t_strategy) {}

void Bot::DoMove() const
{
  // Using strategy to generate move
  Move next_move = this->m_strategy->GenerateMove();
  m_board->SetCell(next_move.x, next_move.y, kBot);
  
}
