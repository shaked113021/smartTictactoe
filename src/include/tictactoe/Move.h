#pragma once

namespace tictactoe
{
struct Move
{
  int x;
  int y;
  int score;

  Move(int t_x, int t_y);
  Move(int t_score);
};
}