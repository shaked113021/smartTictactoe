#include "tictactoe/Move.h"

using namespace tictactoe;

Move::Move(int x_, int y_) {
  x = x_;
  y = y_;
}

Move::Move(int scr) {
  score = scr;
}