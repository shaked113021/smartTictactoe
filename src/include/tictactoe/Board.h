#pragma once
const auto kUser = 1;
const auto kBot = 2;
const auto kUnused = 0;
const auto kTie = 3;
const auto kGamePending = 0;

const int kRowAndCollSize = 3;

namespace tictactoe
{
class Board
{
  public:
    int GetCell(int t_x, int t_y) const;
    void SetCell(int t_x, int t_y, int t_player);
    void SetUserChar(char t_user_char);
    void SetBotChar(char t_bot_char);
    char GetUserChar() const;
    char GetBotChar() const;
    void Reset();
  private:
    int m_game_board[kRowAndCollSize][kRowAndCollSize];
    char m_user_char;
    char m_bot_char;
};
};
