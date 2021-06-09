#include "tictactoe/Board.h"
#include <iostream>
#include <unistd.h>

using namespace tictactoe;

int Board::GetCell(const int t_x, const int t_y) const
{
  return m_game_board[t_y][t_x];
}

void Board::SetCell(const int t_x, const int t_y, const int t_player)
{
  m_game_board[t_y][t_x] = t_player;
}

void Board::SetUserChar(const char t_user_char)
{
  m_user_char = t_user_char;
}

void Board::SetBotChar(const char t_bot_char)
{
  m_bot_char = t_bot_char;
}

void Board::Reset()
{
  for(int i = 0; i < kRowAndCollSize; ++i)
    for(int j = 0; j < kRowAndCollSize; ++j)
    {
      m_game_board[i][j] = 0;
    }
}

char Board::GetUserChar() const
{
  return m_user_char;
}

char Board::GetBotChar() const
{
  return m_bot_char;
}