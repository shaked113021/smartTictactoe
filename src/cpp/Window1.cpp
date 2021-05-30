#include "Window1.h"
#include "findpath.h"
#include "tictactoe/botstrategies/MinimaxStrategy.h"
#include <string>
#include <cstring>

const int kWinEdge = 600;

void Window1::ActivateWindow() {
  // make stylesheet path string
  char stylepath[kStylepathSize];
  sprintf(stylepath, "%s/../Style/Window1.css", exec_path_);
  
  // make window
  this->window_ = gtk_application_window_new (this->app_);
  gtk_window_set_default_size (GTK_WINDOW (this->window_), kWinEdge, kWinEdge);
  gtk_window_set_title (GTK_WINDOW (this->window_), "Tictactoe");
  gtk_window_set_resizable (GTK_WINDOW (this->window_), FALSE);
  gtk_window_set_decorated (GTK_WINDOW (this->window_), FALSE);
  gtk_window_set_position (GTK_WINDOW (this->window_), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (this->window_), 10);
  
  // make button grid
  this->grid_ = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER (this->window_), grid_);
  this->AddButtons();
  
  // load game styling CSS 
  GdkScreen* screen = gdk_screen_get_default();
  GtkCssProvider* provider = gtk_css_provider_new();
  gboolean ret = gtk_css_provider_load_from_path (provider, stylepath,NULL);
  if(ret==FALSE) {
    perror("Failed to load css\n");
    exit(1);
  }
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  gtk_widget_show_all (this->window_);
  this->NewGame();
}


void Window1::FindXY(GtkWidget* button, int& x, int& y)
{
  // for each button, find if it's pointer matches to given button
  for(int i = 0; i < kRowAndCollSize; ++i)
    for(int j = 0; j < kRowAndCollSize; ++j)
      if(gtk_grid_get_child_at(GTK_GRID(this->grid_), j, i) == button) {
        x = j;
        y = i;
        return;
      }

  // if we didn't found button, we return -1
  x = kXYNotFound;
  y = kXYNotFound;
  return;
}

int Window1::ShowMessage(ButtonType_ buttons, gchar* message) {
  // declarations
  GtkWidget* dialog;
  int flags = GTK_DIALOG_DESTROY_WITH_PARENT;
  int type = GTK_MESSAGE_OTHER;
  
  // showing dialog
  dialog = gtk_message_dialog_new (GTK_WINDOW (this->window_), (GtkDialogFlags)flags, (GtkMessageType)type, (GtkButtonsType)buttons, "%s",message);
  int response = gtk_dialog_run(GTK_DIALOG (dialog));
  
  // as long as we don't have clear answer, show user the dialog
  while(response == GTK_RESPONSE_CLOSE) {
    response = gtk_dialog_run(GTK_DIALOG (dialog));
  }

  gtk_widget_destroy (dialog); // the garbege truck comes...
  return response;
}

void Window1::UpdateButtons() {
  // declarations
  GtkWidget* button;
  gchar bot_char[kBotCharSize];
  gchar user_char[kUserCharSize];

  // getting user char and bot char from board_
  sprintf(bot_char,(char *)"%c", this->board_->GetBotChar());  
  sprintf(user_char, (char*)"%c", this->board_->GetUserChar());

  // for each button, set name and label according to corresponding board cell
  for(int i=0; i < kRowAndCollSize; i++) {
    for(int j = 0; j < kRowAndCollSize; j++) {
      button = gtk_grid_get_child_at(GTK_GRID (this->grid_), j, i);
      switch (this->board_->GetCell(j, i)) {
        case kUser: {
          gtk_button_set_label (GTK_BUTTON (button), user_char);
          gtk_widget_set_name (button, "user");
          break;
        }
        case kBot: {
          gtk_button_set_label (GTK_BUTTON (button), bot_char);
          gtk_widget_set_name (button, "bot");
          break;
        }
        case kUnused: {
          gtk_button_set_label (GTK_BUTTON (button), " ");
          gtk_widget_set_name (button, "default");
          break;
        }
        default: {
          g_print("Invalid argument in update Buttons\n");
        }
      }
    }
  }
}

void Window1::ParseEndGameResponse(int response)
{
  switch(response) {
    case GTK_RESPONSE_YES: {
      this->NewGame();
      break;
    }
    case GTK_RESPONSE_NO: {
      g_application_quit(G_APPLICATION (this->app_));
      break;
    }
    default: {
      break;
    }
  }
}

void Window1::GridButtonListener(GtkWidget* button) {
  // if game is ended. return
  this->victory_status_ = this->victory_checker_->Check();
  if(this->victory_status_ != kGamePending) return;
  
  // declarations
  int x;
  int y;
  
  // find buttons, if not found or if button is used return
  FindXY(button, x, y);
  if((x == kXYNotFound) || (y == kXYNotFound)) return;
  if(this->board_->GetCell (x, y) != kUnused) return;
  
  // setting chosen cell to user
  this->board_->SetCell(x, y, kUser);
  this->UpdateButtons();
  
  // checking victory and display messages accordingly
  this->victory_status_ = this->victory_checker_->Check();
  if(this->victory_status_ == kUser) {
    int response = ShowMessage(YES_NO,(gchar *)"Yay! you Won!\nDo you want to another game?");
    this->ParseEndGameResponse(response);
    return;
  } else if(victory_status_ == kTie) {
    int response = ShowMessage(YES_NO, (gchar *)"Oh it\'s a tie! :\(\nDo you want to try Again?");
    this->ParseEndGameResponse (response);
    return;
  }
  
  // do bot turn
  this->BotTurn();
}

void Window1::BotTurn() {
  // if game ended return
  this->victory_status_ = this->victory_checker_->Check();
  if(this->victory_status_ != kGamePending) return;
  
  // do bot move
  this->game_bot_->DoMove();
  this->UpdateButtons();
  
  // checking victory and display messages accordingly
  this->victory_status_ = this->victory_checker_->Check();
  int response;
  switch(this->victory_status_) {
    case kBot: {
      response = ShowMessage(YES_NO, (gchar *) "Oh you lost :\(\nDo you want to try again?");
      this->ParseEndGameResponse(response);
      return;
      break;
    }
    case kUser: {
      response = ShowMessage(YES_NO, (gchar*)"Oh it\'s a tie! :\(\nDo you want to try Again?");
      this->ParseEndGameResponse(response);
      return;
      break;
    }
    default: {
      break;
    }
  }
}

static void Activate(GtkApplication *Napp, Window1 &data) {
  // at activation, call window activation
  data.ActivateWindow();
}

Window1::Window1(int argc, char** argv) {   
  // initialize objects
  this->board_ = new tictactoe::Board;
  this->victory_checker_= new tictactoe::VictoryChecker(this->board_);
  this->strategy_ = new tictactoe::botstrategies::MinimaxStrategy(this->board_, this->victory_checker_);
  this->game_bot_ = new tictactoe::Bot(this->board_, strategy_);

  // find execution path
  std::string execpathstr = FindPath();
  this->exec_path_ = new char[execpathstr.size() + 1];
  strcpy(exec_path_, execpathstr.c_str());

  // initialize application
  this->app_ = gtk_application_new ("shakedcohen.tictactoe", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (this->app_, "activate", G_CALLBACK (Activate), this);
  this->status_ = g_application_run (G_APPLICATION (this->app_), argc, argv);
  g_object_unref(this->app_); // the garbage truck comes...

  // handle exit
  if(this->status_ != 0) exit(this->status_);
}

void Window1::NewGame() {
  // reset board in a new game
  this->board_->ResetBoard();
  this->UpdateButtons();
  this->victory_status_ = 0;

  // ask user if it wants to be first
  int user_response = ShowMessage(YES_NO, (gchar *)"Do you want to be first?");
  switch(user_response) {
    case GTK_RESPONSE_YES: {
      this->board_->SetBotChar('O');
      this->board_->SetUserChar('X');
      break;
    }
    case GTK_RESPONSE_NO: {
      this->board_->SetBotChar('X');
      this->board_->SetUserChar('O');
      this->BotTurn();
      break;
    }    
  }
}

Window1::~Window1() {
  // cleaning the garbage
  delete this->game_bot_;
  delete this->strategy_;
  delete this->board_;
  delete this->exec_path_;
}

// click handler
static void OnGridButtonPress(GtkWidget *button, Window1 &data) {
  data.GridButtonListener(button);
}

void Window1::AddButtons() {
  // declarations
  GtkWidget* button;
  int button_edge = kWinEdge / kRowAndCollSize;

  // for each cell in board, create new button and add to grid
  for(int i = 0; i < kRowAndCollSize; ++i)
    for(int j = 0; j < kRowAndCollSize; ++j) {
      button = gtk_button_new();
      gtk_widget_set_size_request (button, button_edge, button_edge);
      g_signal_connect (button, "clicked", G_CALLBACK(OnGridButtonPress), this);
      gtk_grid_attach (GTK_GRID (this->grid_), button, j, i, kButtonWidthCells, kButtonHeightCells);
    }
}