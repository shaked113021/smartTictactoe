#pragma once
#include "Board.h"
namespace tictactoe {
class Bot {
  public:
    void DoMove(Board* board);
    void SetIsFirst(bool);
  private:
    struct Move_ {
      int x;
      int y;
      int score;
      Move_(int mx, int my){x = mx, y= my;};
      Move_(int scr) {score = scr;};
    };

    Move_ Minimax(Board* board, int player);
    void DoRandom(Board* board);
    bool is_first_ = true;
};
};
