#pragma once
#include <gtk/gtk.h>
#include "tictactoe/Board.h"
#include "tictactoe/Bot.h"
#include "tictactoe/VictoryChecker.h"
#include "tictactoe/botstrategies/IStrategy.h"


class Window1
{
  private:
    tictactoe::Bot *m_game_bot;
    tictactoe::Board *m_board;
    tictactoe::botstrategies::IStrategy* m_strategy;
    tictactoe::VictoryChecker *m_victory_checker;
    GtkWidget *m_window;
    GtkWidget *m_grid;
    GtkApplication *m_app;
    char* m_exec_path;
    int m_victory_status;
    int m_status;
    static const auto kXYNotFound = -1;
    static const auto kStylepathSize = 80;
    static const auto kBotCharSize = 5;
    static const auto kUserCharSize = 5;
    static const auto kButtonWidthCells = 1;
    static const auto kButtonHeightCells = 1;

    void AddButtons();
    void FindXY(GtkWidget* t_button, int &t_x, int &t_y);
    void UpdateButtons();
    enum ButtonType
    {
      OK = GTK_BUTTONS_OK,
      CLOSE = GTK_BUTTONS_CLOSE,
      CANCEL = GTK_BUTTONS_CANCEL,
      YES_NO = GTK_BUTTONS_YES_NO,
      OK_CANCEL = GTK_BUTTONS_OK_CANCEL
      };
    int ShowMessage(ButtonType t_buttons, gchar* t_message);
    void ParseEndGameResponse(int t_response);
    void BotTurn();
    void NewGame();
  public:
    Window1(const Window1&) = delete;
    Window1(int argc, char** argv);
    void GridButtonListener(GtkWidget* t_button);
    void ActivateWindow();
    ~Window1();
};