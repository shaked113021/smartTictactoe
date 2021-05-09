#include "Headers/Window1.h"
#include "Headers/findpath.h"
#include <string>
#include <cstring>

const int kWinEdge = 600;

void Window1::ActivateWindow() {
    char stylepath[80];
    sprintf(stylepath, "%s/../Style/Window1.css", exec_path_);
    window_ = gtk_application_window_new (app_);
    gtk_window_set_default_size (GTK_WINDOW (window_), kWinEdge, kWinEdge);
    gtk_window_set_title (GTK_WINDOW (window_), "Tictactoe");
    gtk_window_set_resizable (GTK_WINDOW (window_), FALSE);
    gtk_window_set_decorated (GTK_WINDOW (window_), FALSE);
    gtk_window_set_position (GTK_WINDOW (window_), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (window_), 10);

    grid_ = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window_), grid_);

    AddButtons();
    GdkScreen *screen = gdk_screen_get_default();
    GtkCssProvider *provider = gtk_css_provider_new();
    gboolean ret = gtk_css_provider_load_from_path (provider, stylepath,NULL);
    if(ret==FALSE) {
        perror("Failed to load css\n");
        exit(1);
    }
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_widget_show_all (window_);
    NewGame();
}


void Window1::FindXY(GtkWidget *button, int &x, int &y)
{
    for(int i = 0; i < kRowAndCollSize; i++)
        for(int j = 0; j < kRowAndCollSize; j++)
            if(gtk_grid_get_child_at(GTK_GRID(grid_), j, i) == button) {
                x = j;
                y = i;
                return;
            }
    x = -1;
    y=-1;
    return;
}

int Window1::ShowMessage(ButtonType_ buttons, gchar * message) {
    GtkWidget *dialog;
    int flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    int type = GTK_MESSAGE_OTHER;
    
    dialog = gtk_message_dialog_new (GTK_WINDOW (window_), (GtkDialogFlags)flags, (GtkMessageType)type, (GtkButtonsType)buttons, "%s",message);
    int ret = gtk_dialog_run(GTK_DIALOG (dialog));
    while(ret == GTK_RESPONSE_CLOSE) ret = gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
    return ret;
}

void Window1::UpdateButtons() {
    GtkWidget *button;
    gchar bot_char[5];
    sprintf(bot_char,(char *)"%c", board_->GetBotChar());
    gchar user_char[5];
    sprintf(user_char, (char*)"%c", board_->GetUserChar());

    for(int i=0; i < kRowAndCollSize; i++)
        for(int j = 0; j < kRowAndCollSize; j++) {
            button = gtk_grid_get_child_at(GTK_GRID (grid_), j, i);
            switch (board_->GetCell(j, i)) {
                case kUser:
                    gtk_button_set_label (GTK_BUTTON (button), user_char);
                    gtk_widget_set_name (button, "user");
                    break;
                case kBot:
                    gtk_button_set_label (GTK_BUTTON (button), bot_char);
                    gtk_widget_set_name (button, "bot");
                    break;
                case kUnused:
                    gtk_button_set_label (GTK_BUTTON (button), " ");
                    gtk_widget_set_name (button, "default");
                    break;
                default:
                    g_print("Invalid argument in update Buttons\n");
            }
        }
}

void Window1::ParseResponse(int ret)
{
    switch(ret) {
        case GTK_RESPONSE_YES:
            NewGame();
            break;
        case GTK_RESPONSE_NO:
            g_application_quit(G_APPLICATION (app_));
            break;
        default:
            break;
    }
}

void Window1::GridButtonListener(GtkWidget *button) {
    victory_status_ = board_->CheckVictory();
    if(victory_status_ != 0) return;
    int x, y;
    FindXY(button, x, y);
    if(x == -1 || y == -1) return;
    if(board_->GetCell (x, y) != kUnused) return;
    
    board_->SetCell(x, y, kUser);
    UpdateButtons();
    
    victory_status_ = board_->CheckVictory();
    if(victory_status_ == kUser) {
        int ret = ShowMessage(YES_NO,(gchar *)"Yay! you Won!\nDo you want to another game?");
        ParseResponse(ret);
        return;
    } else if(victory_status_ == kTie) {
        int ret = ShowMessage(YES_NO, (gchar *)"Oh it\'s a tie! :\(\nDo you want to try Again?");
        ParseResponse (ret);
        return;
    }
    
    BotTurn();
}

void Window1::BotTurn() {
    victory_status_ = board_->CheckVictory();
    if(victory_status_ != 0) return;
    game_bot_->DoMove(board_);
    UpdateButtons();
    
    victory_status_ = board_->CheckVictory();
    int ret;
    switch(victory_status_) {
        case kBot:
            ret = ShowMessage(YES_NO, (gchar *) "Oh you lost :\(\nDo you want to try again?");
            ParseResponse(ret);
            return;
            break;
        case kUser:
            ret = ShowMessage(YES_NO, (gchar*)"Oh it\'s a tie! :\(\nDo you want to try Again?");
            ParseResponse(ret);
            return;
            break;
        default:
            break;
    }
}

static void Activate(GtkApplication *Napp, Window1 &data) {
    data.ActivateWindow();
    Napp = NULL;
    delete Napp;
}

Window1::Window1(int argc, char **argv) {   
    game_bot_ = new tictactoe::Bot;
    board_ = new tictactoe::Board;
    std::string execpathstr = findpath();
    exec_path_ = new char[execpathstr.size() + 1];
    strcpy(exec_path_, execpathstr.c_str());

    app_ = gtk_application_new ("shakedcohen.tictactoe", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app_, "activate", G_CALLBACK (Activate), this);
    status_ = g_application_run (G_APPLICATION (app_), argc, argv);
    g_object_unref(app_);

    if(status_ != 0) exit(status_);
}

void Window1::NewGame() {
    board_->ResetBoard();
    UpdateButtons();
    victory_status_ = 0;
    int ret = ShowMessage(YES_NO, (gchar *)"Do you want to be first?");
    switch(ret) {
        case GTK_RESPONSE_YES:
            board_->SetBotChar('O');
            board_->SetUserChar('X');
            break;
        case GTK_RESPONSE_NO:
            board_->SetBotChar('X');
            board_->SetUserChar('O');
            BotTurn();
            break;
            
    }
}

Window1::~Window1() {
    delete game_bot_;
    delete board_;
    delete exec_path_;
}



static void onGridButtonPress(GtkWidget *button, Window1 &data) {
    data.GridButtonListener(button);
}

void Window1::AddButtons() {
    GtkWidget *button;
    int button_edge = kWinEdge / kRowAndCollSize;
    for(int i = 0; i < kRowAndCollSize; i++)
        for(int j = 0; j < kRowAndCollSize; j++) {
            button = gtk_button_new();
            gtk_widget_set_size_request (button, button_edge, button_edge);
            g_signal_connect (button, "clicked", G_CALLBACK(onGridButtonPress), this);
            gtk_grid_attach (GTK_GRID (grid_), button, j, i, 1,1);
        }
}