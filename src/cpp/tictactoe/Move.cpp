#include "tictactoe/Move.h"

using namespace tictactoe;

Move::Move(const int t_x, const int t_y)
{
  x = t_x;
  y = t_y;
}

Move::Move(const int t_score)
{
  score = t_score;
}