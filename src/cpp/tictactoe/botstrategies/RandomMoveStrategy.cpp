#include "tictactoe/botstrategies/RandomMoveStrategy.h"
#include <cmath>

using namespace tictactoe;
using namespace tictactoe::botstrategies;

RandomMoveStrategy::RandomMoveStrategy(const Board *t_board) : m_board((Board*)t_board) {}

RandomMoveStrategy::~RandomMoveStrategy() {}

Move RandomMoveStrategy::GenerateMove() {
  int x;  
  int y;
  
  // generate random x and y until hitting a clear spot
  do{
    x = rand() % (kRowAndCollSize - 1);
    y = rand() % (kRowAndCollSize - 1);
  } while(this->m_board->GetCell(x,y) != kUnused);
  
  return Move(x, y);
}