#include "tictactoe/botstrategies/RandomMoveStrategy.h"
#include <cmath>

using namespace tictactoe;
using namespace tictactoe::botstrategies;

RandomMoveStrategy::RandomMoveStrategy(Board *board) : board_(board) {}

RandomMoveStrategy::~RandomMoveStrategy() {}

Move RandomMoveStrategy::GenerateMove() {
  int x;  
  int y;
  
  // generate random x and y until hitting a clear spot
  do{
    x = rand() % (kRowAndCollSize - 1);
    y = rand() % (kRowAndCollSize - 1);
  } while(this->board_->GetCell(x,y) != kUnused);
  
  return Move(x, y);
}