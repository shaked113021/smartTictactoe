#pragma once
#include <gtk/gtk.h>
#include "Bot.h"


class Window1 {
    private:
        Bot *gameBot;
        Board *board;
        GtkWidget *window;
        GtkWidget *grid;
        GtkApplication *app;
        char *execpath;
        void addButtons();
        void findXY(GtkWidget *button, int &x, int &y);
        void updateButtons();
        int victoryStatus;
        enum buttonType {
            OK = GTK_BUTTONS_OK,
            CLOSE = GTK_BUTTONS_CLOSE,
            CANCEL = GTK_BUTTONS_CANCEL,
            YES_NO = GTK_BUTTONS_YES_NO,
            OK_CANCEL = GTK_BUTTONS_OK_CANCEL
        };
        int showMessage(buttonType buttons, gchar * message);
        void parseResponse(int ret);
        void botTurn();
        int status;
        void new_game();

    public:
        Window1(int argc, char **argv);
        void gridButtonListener(GtkWidget *button);
        void activateWindow();
        ~Window1();
};