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

    static const int kUserWinScore = -1;
    static const int kBotWinScore = 1;
    static const int kTieScore = 0;
    static const int kGamePending = 0;
    Move_ Minimax(Board* board, int player);
    void DoRandom(Board* board);
    bool is_first_ = true;
};
};
