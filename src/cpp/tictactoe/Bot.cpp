#include "tictactoe/Bot.h"
#include "tictactoe/Move.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <memory>

using namespace tictactoe;
using namespace botstrategies;

// getting board and victory checker in constractor
Bot::Bot(Board* board, IStrategy* strategy) : board_(board), strategy_(strategy) {}

void Bot::DoMove() const {
  // Using strategy to generate move
  Move next_move = this->strategy_->GenerateMove();
  board_->SetCell(next_move.x, next_move.y, kBot);
  
}
