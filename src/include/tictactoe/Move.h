#pragma once

namespace tictactoe
{
struct Move
{
  int x;
  int y;
  int score;

  Move(const int t_x, const int t_y);
  Move(const int t_score);
};
}