#include "Headers/Window1.h"
#define N 3
const int WINEDGE = 600;

void Window1::activateWindow()
{
    window = gtk_application_window_new (app);
    gtk_window_set_default_size (GTK_WINDOW (window), WINEDGE, WINEDGE);
    gtk_window_set_title (GTK_WINDOW (window), "Tictactoe");
    gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
    gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER (window), grid);

    addButtons();
    GdkScreen *screen = gdk_screen_get_default();
    GtkCssProvider *provider = gtk_css_provider_new();
    gboolean ret = gtk_css_provider_load_from_path (provider, "src/Style/Window1.css",NULL);
    if(ret==FALSE)
    {
        perror("Failed to load css\n");
        exit(1);
    }
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_widget_show_all (window);
    new_game();
}


void Window1::findXY(GtkWidget *button, int &x, int &y)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(gtk_grid_get_child_at(GTK_GRID(grid), j, i) == button)
            {
                x = j;
                y = i;
                return;
            }
    x = -1;
    y=-1;
    return;
}

int Window1::showMessage(buttonType buttons, gchar * message)
{
    GtkWidget *dialog;
    int flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    int type = GTK_MESSAGE_OTHER;
    
    dialog = gtk_message_dialog_new (GTK_WINDOW (window), (GtkDialogFlags)flags, (GtkMessageType)type, (GtkButtonsType)buttons, "%s",message);
    int ret = gtk_dialog_run(GTK_DIALOG (dialog));
    while(ret == GTK_RESPONSE_CLOSE) ret = gtk_dialog_run(GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
    return ret;
}

void Window1::updateButtons()
{
    GtkWidget *button;
    gchar botChar[5];
    sprintf(botChar,(char *)"%c", board->getBotChar());
    gchar userChar[5];
    sprintf(userChar, (char*)"%c", board->getUserChar());

    for(int i=0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            button = gtk_grid_get_child_at(GTK_GRID (grid), j, i);
            switch (board->getCell(j, i))
            {
                case USER:
                    gtk_button_set_label (GTK_BUTTON (button), userChar);
                    gtk_widget_set_name (button, "user");
                    break;
                case BOT:
                    gtk_button_set_label (GTK_BUTTON (button), botChar);
                    gtk_widget_set_name (button, "bot");
                    break;
                case UNUSED:
                    gtk_button_set_label (GTK_BUTTON (button), " ");
                    gtk_widget_set_name (button, "default");
                    break;
                default:
                    g_print("Invalid argument in update Buttons\n");
            }
        }
}

void Window1::parseResponse(int ret)
{
    switch(ret)
    {
        case GTK_RESPONSE_YES:
            new_game();
            break;
        case GTK_RESPONSE_NO:
            g_application_quit(G_APPLICATION (app));
            break;
        default:
            break;
    }
}

void Window1::gridButtonListener(GtkWidget *button)
{
    victoryStatus = board->checkVictory();
    if(victoryStatus != 0) return;
    int x, y;
    findXY(button, x, y);
    if(x == -1 || y == -1) return;
    if(board->getCell (x, y) != UNUSED) return;
    
    board->setCell(x, y, USER);
    updateButtons();
    
    victoryStatus = board->checkVictory();
    if(victoryStatus == USER)
    {
        int ret = showMessage(YES_NO,(gchar *)"Yay! you Won!\nDo you want to another game?");
        parseResponse(ret);
        return;
    } else if(victoryStatus == TIE)
    {
        int ret = showMessage(YES_NO, (gchar *)"Oh it\'s a tie! :\(\nDo you want to try Again?");
        parseResponse (ret);
        return;
    }
    
    botTurn();
}

void Window1::botTurn()
{
    victoryStatus = board->checkVictory();
    if(victoryStatus != 0) return;
    gameBot->doMove(board);
    updateButtons();
    
    victoryStatus = board->checkVictory();
    int ret;
    switch(victoryStatus)
    {
        case BOT:
            ret = showMessage(YES_NO, (gchar *) "Oh you lost :\(\nDo you want to try again?");
            parseResponse(ret);
            return;
            break;
        case USER:
            ret = showMessage(YES_NO, (gchar*)"Oh it\'s a tie! :\(\nDo you want to try Again?");
            parseResponse(ret);
            return;
            break;
        default:
            break;
    }
}

static void activate(GtkApplication *Napp, Window1 &data)
{
    data.activateWindow();
    Napp = NULL;
    delete Napp;
}

Window1::Window1(int argc, char **argv)
{

    
    gameBot = new Bot;
    board = new Board;

    app = gtk_application_new ("shakedcohen.tictactoe", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), this);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref(app);

    if(status != 0) exit(status);
}

void Window1::new_game()
{
    board->resetBoard();
    updateButtons();
    victoryStatus = 0;
    int ret = showMessage(YES_NO, (gchar *)"Do you want to be first?");
    switch(ret)
    {
        case GTK_RESPONSE_YES:
            board->setBotChar('O');
            board->setUserChar('X');
            break;
        case GTK_RESPONSE_NO:
            board->setBotChar('X');
            board->setUserChar('O');
            botTurn();
            break;
            
    }
}

Window1::~Window1()
{
    delete gameBot;
    delete board;
}



static void onGridButtonPress(GtkWidget *button, Window1 &data)
{
    data.gridButtonListener(button);
}

void Window1::addButtons()
{
    GtkWidget *button;
    int buttonEdge = WINEDGE / N;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            button = gtk_button_new();
            gtk_widget_set_size_request (button, buttonEdge, buttonEdge);
            g_signal_connect (button, "clicked", G_CALLBACK(onGridButtonPress), this);
            gtk_grid_attach (GTK_GRID (grid), button, j, i, 1,1);
        }
}