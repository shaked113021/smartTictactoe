#include "tictactoe/botstrategies/RandomStrategy.h"
#include <cmath>

using namespace tictactoe::botstrategies;

RandomStrategy::RandomStrategy(Board *board) : board_(board) {}

void RandomStrategy::DoMove() {
  int x;
  int y;
  
  // generate random x and y until hitting a clear spot
  do{
    x = rand() % (kRowAndCollSize - 1);
    y = rand() % (kRowAndCollSize - 1);
  } while(this->board_->GetCell(x,y) != kUnused);
  this->board_->SetCell(x, y, kBot);
}