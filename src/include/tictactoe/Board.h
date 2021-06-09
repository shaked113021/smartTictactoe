#pragma once
const auto kUser = 1;
const auto kBot = 2;
const auto kUnused = 0;
const auto kTie = 3;
const auto kGamePending = 0;

const auto kRowAndCollSize = 3;

namespace tictactoe
{
class Board
{
  public:
    int GetCell(const int t_x, const int t_y) const;
    void SetCell(const int t_x, const int t_y, const int t_player);
    void SetUserChar(const char t_user_char);
    void SetBotChar(const char t_bot_char);
    char GetUserChar() const;
    char GetBotChar() const;
    void Reset();
  private:
    int m_game_board[kRowAndCollSize][kRowAndCollSize];
    char m_user_char;
    char m_bot_char;
};
};
