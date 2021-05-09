#pragma once
const int kUser = 1;
const int kBot = 2;
const int kUnused = 0;
const int kTie = 3;
const int kGamePending = 0;

const int kRowAndCollSize = 3;

namespace tictactoe {
class Board {
  public:
    int GetCell(int x, int y) const;
    void SetCell(int x, int y, int player);
    void SetUserChar(char c);
    void SetBotChar(char c);
    char GetUserChar() const;
    char GetBotChar() const;
    void ResetBoard();
  private:
    int game_board_[kRowAndCollSize][kRowAndCollSize];
    char user_char_;
    char bot_char_;
};
};
