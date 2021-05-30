#include "tictactoe/Move.h"

using namespace tictactoe;

Move::Move(int t_x, int t_y)
{
  x = t_x;
  y = t_y;
}

Move::Move(int t_score)
{
  score = t_score;
}