#pragma once
#include <gtk/gtk.h>
#include "Bot.h"


class Window1 {
  private:
    tictactoe::Bot *game_bot_;
    tictactoe::Board *board_;
    GtkWidget *window_;
    GtkWidget *grid_;
    GtkApplication *app_;
    char* exec_path_;
    int victory_status_;
    int status_;
    void AddButtons();
    void FindXY(GtkWidget* button, int &x, int &y);
    void UpdateButtons();
    enum ButtonType_ {
      OK = GTK_BUTTONS_OK,
      CLOSE = GTK_BUTTONS_CLOSE,
      CANCEL = GTK_BUTTONS_CANCEL,
      YES_NO = GTK_BUTTONS_YES_NO,
      OK_CANCEL = GTK_BUTTONS_OK_CANCEL
      };
      int ShowMessage(ButtonType_ buttons, gchar* message);
      void ParseResponse(int ret);
      void BotTurn();
      void NewGame();

  public:
    Window1(int argc, char** argv);
    void GridButtonListener(GtkWidget* button);
    void ActivateWindow();
    ~Window1();
};