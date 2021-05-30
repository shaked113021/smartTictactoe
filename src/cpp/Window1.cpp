#include "Window1.h"
#include "findpath.h"
#include "tictactoe/botstrategies/MinimaxStrategy.h"
#include <string>
#include <cstring>

const int kWinEdge = 600;

void Window1::ActivateWindow()
{
  // make stylesheet path string
  char stylepath[kStylepathSize];
  sprintf(stylepath, "%s/../Style/Window1.css", m_exec_path);
  
  // make window
  this->m_window = gtk_application_window_new (this->m_app);
  gtk_window_set_default_size (GTK_WINDOW (this->m_window), kWinEdge, kWinEdge);
  gtk_window_set_title (GTK_WINDOW (this->m_window), "Tictactoe");
  gtk_window_set_resizable (GTK_WINDOW (this->m_window), FALSE);
  gtk_window_set_decorated (GTK_WINDOW (this->m_window), FALSE);
  gtk_window_set_position (GTK_WINDOW (this->m_window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (this->m_window), 10);
  
  // make button grid
  this->m_grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER (this->m_window), m_grid);
  this->AddButtons();
  
  // load game styling CSS 
  GdkScreen* screen = gdk_screen_get_default();
  GtkCssProvider* provider = gtk_css_provider_new();
  gboolean ret = gtk_css_provider_load_from_path (provider, stylepath,NULL);
  if(ret==FALSE)
  {
    perror("Failed to load css\n");
    exit(1);
  }
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  gtk_widget_show_all (this->m_window);
  this->NewGame();
}


void Window1::FindXY(GtkWidget* t_button, int& t_x, int& t_y)
{
  // for each button, find if it's pointer matches to given button
  for(int i = 0; i < kRowAndCollSize; ++i)
    for(int j = 0; j < kRowAndCollSize; ++j)
      if(gtk_grid_get_child_at(GTK_GRID(this->m_grid), j, i) == t_button)
      {
        t_x = j;
        t_y = i;
        return;
      }

  // if we didn't found button, we return -1
  t_x = kXYNotFound;
  t_y = kXYNotFound;
  return;
}

int Window1::ShowMessage(ButtonType t_buttons, gchar* t_message)
{
  // declarations
  GtkWidget* dialog;
  int flags = GTK_DIALOG_DESTROY_WITH_PARENT;
  int type = GTK_MESSAGE_OTHER;
  
  // showing dialog
  dialog = gtk_message_dialog_new (GTK_WINDOW (this->m_window), (GtkDialogFlags)flags, (GtkMessageType)type, (GtkButtonsType)t_buttons, "%s",t_message);
  int response = gtk_dialog_run(GTK_DIALOG (dialog));
  
  // as long as we don't have clear answer, show user the dialog
  while(response == GTK_RESPONSE_CLOSE)
  {
    response = gtk_dialog_run(GTK_DIALOG (dialog));
  }

  gtk_widget_destroy (dialog); // the garbege truck comes...
  return response;
}

void Window1::UpdateButtons()
{
  // declarations
  GtkWidget* button;
  gchar bot_char[kBotCharSize];
  gchar user_char[kUserCharSize];

  // getting user char and bot char from board_
  sprintf(bot_char,(char *)"%c", this->m_board->GetBotChar());  
  sprintf(user_char, (char*)"%c", this->m_board->GetUserChar());

  // for each button, set name and label according to corresponding board cell
  for(int i=0; i < kRowAndCollSize; ++i)
  {
    for(int j = 0; j < kRowAndCollSize; ++j)
    {
      button = gtk_grid_get_child_at(GTK_GRID (this->m_grid), j, i);
      switch (this->m_board->GetCell(j, i))
      {
        case kUser:
        {
          gtk_button_set_label (GTK_BUTTON (button), user_char);
          gtk_widget_set_name (button, "user");
          break;
        }
        case kBot:
        {
          gtk_button_set_label (GTK_BUTTON (button), bot_char);
          gtk_widget_set_name (button, "bot");
          break;
        }
        case kUnused:
        {
          gtk_button_set_label (GTK_BUTTON (button), " ");
          gtk_widget_set_name (button, "default");
          break;
        }
        default:
        {
          g_print("Invalid argument in update Buttons\n");
        }
      }
    }
  }
}

void Window1::ParseEndGameResponse(int t_response)
{
  switch(t_response)
  {
    case GTK_RESPONSE_YES:
    {
      this->NewGame();
      break;
    }
    case GTK_RESPONSE_NO:
    {
      g_application_quit(G_APPLICATION (this->m_app));
      break;
    }
    default:
    {
      break;
    }
  }
}

void Window1::GridButtonListener(GtkWidget* t_button)
{
  // if game is ended. return
  this->m_victory_status = this->m_victory_checker->Check();
  if(this->m_victory_status != kGamePending) return;
  
  // declarations
  int x;
  int y;
  
  // find buttons, if not found or if button is used return
  FindXY(t_button, x, y);
  if((x == kXYNotFound) || (y == kXYNotFound)) return;
  if(this->m_board->GetCell (x, y) != kUnused) return;
  
  // setting chosen cell to user
  this->m_board->SetCell(x, y, kUser);
  this->UpdateButtons();
  
  // checking victory and display messages accordingly
  this->m_victory_status = this->m_victory_checker->Check();
  if(this->m_victory_status == kUser)
  {
    int response = ShowMessage(YES_NO,(gchar *)"Yay! you Won!\nDo you want to another game?");
    this->ParseEndGameResponse(response);
    return;
  } else if(m_victory_status == kTie)
  {
    int response = ShowMessage(YES_NO, (gchar *)"Oh it\'s a tie! :\(\nDo you want to try Again?");
    this->ParseEndGameResponse (response);
    return;
  }
  
  // do bot turn
  this->BotTurn();
}

void Window1::BotTurn()
{
  // if game ended return
  this->m_victory_status = this->m_victory_checker->Check();
  if(this->m_victory_status != kGamePending) return;
  
  // do bot move
  this->m_game_bot->DoMove();
  this->UpdateButtons();
  
  // checking victory and display messages accordingly
  this->m_victory_status = this->m_victory_checker->Check();
  int response;
  switch(this->m_victory_status)
  {
    case kBot:
    {
      response = ShowMessage(YES_NO, (gchar *) "Oh you lost :\(\nDo you want to try again?");
      this->ParseEndGameResponse(response);
      return;
      break;
    }
    case kUser:
    {
      response = ShowMessage(YES_NO, (gchar*)"Oh it\'s a tie! :\(\nDo you want to try Again?");
      this->ParseEndGameResponse(response);
      return;
      break;
    }
    default:
    {
      break;
    }
  }
}

static void Activate(GtkApplication *t_Napp, Window1 &t_data)
{
  // at activation, call window activation
  t_data.ActivateWindow();
}

Window1::Window1(int argc, char** argv)
{   
  // initialize objects
  this->m_board = new tictactoe::Board;
  this->m_victory_checker= new tictactoe::VictoryChecker(this->m_board);
  this->m_strategy = new tictactoe::botstrategies::MinimaxStrategy(this->m_board, this->m_victory_checker);
  this->m_game_bot = new tictactoe::Bot(this->m_board, m_strategy);

  // find execution path
  std::string execpathstr = FindPath();
  this->m_exec_path = new char[execpathstr.size() + 1];
  strcpy(m_exec_path, execpathstr.c_str());

  // initialize application
  this->m_app = gtk_application_new ("shakedcohen.tictactoe", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (this->m_app, "activate", G_CALLBACK (Activate), this);
  this->m_status = g_application_run (G_APPLICATION (this->m_app), argc, argv);
  g_object_unref(this->m_app); // the garbage truck comes...

  // handle exit
  if(this->m_status != 0) exit(this->m_status);
}

void Window1::NewGame()
{
  // reset board in a new game
  this->m_board->Reset();
  this->UpdateButtons();
  this->m_victory_status = 0;

  // ask user if it wants to be first
  int user_response = ShowMessage(YES_NO, (gchar *)"Do you want to be first?");
  switch(user_response)
  {
    case GTK_RESPONSE_YES:
    {
      this->m_board->SetBotChar('O');
      this->m_board->SetUserChar('X');
      break;
    }
    case GTK_RESPONSE_NO:
    {
      this->m_board->SetBotChar('X');
      this->m_board->SetUserChar('O');
      this->BotTurn();
      break;
    }    
  }
}

Window1::~Window1()
{
  // cleaning the garbage
  delete this->m_game_bot;
  delete this->m_strategy;
  delete this->m_board;
  delete this->m_exec_path;
}

// click handler
static void OnGridButtonPress(GtkWidget *t_button, Window1 &t_data)
{
  t_data.GridButtonListener(t_button);
}

void Window1::AddButtons()
{
  // declarations
  GtkWidget* button;
  int button_edge = kWinEdge / kRowAndCollSize;

  // for each cell in board, create new button and add to grid
  for(int i = 0; i < kRowAndCollSize; ++i)
    for(int j = 0; j < kRowAndCollSize; ++j)
    {
      button = gtk_button_new();
      gtk_widget_set_size_request (button, button_edge, button_edge);
      g_signal_connect (button, "clicked", G_CALLBACK(OnGridButtonPress), this);
      gtk_grid_attach (GTK_GRID (this->m_grid), button, j, i, kButtonWidthCells, kButtonHeightCells);
    }
}