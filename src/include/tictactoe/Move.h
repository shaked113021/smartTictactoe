#pragma once

namespace tictactoe {
struct Move {
  int x;
  int y;
  int score;

  Move(int x_, int y_);
  Move(int scr);
};
}