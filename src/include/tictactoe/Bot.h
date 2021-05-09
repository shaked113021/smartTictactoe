#pragma once
#include "Board.h"
#include "VictoryChecker.h"

namespace tictactoe {
class Bot {
  public:
    Bot(Board* board, VictoryChecker* victory_checker);
    void DoMove();
    void SetIsFirst(bool);
  private:
    Board* board_;
    VictoryChecker* victory_checker_;
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
    Move_ Minimax(int player);
    void DoRandom();
    bool is_first_ = true;
};
};
