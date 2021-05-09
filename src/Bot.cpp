#include "Headers/Bot.h"
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace tictactoe;

void Bot::DoMove(Board* board) {
  // if this is first move, we don't need to run minimax evaluation on board
  if (this->is_first_) {
    this->DoRandom(board);
    this->is_first_ = false;
  } else {
    Move_ ret = Minimax(board, kBot);
    board->SetCell(ret.x, ret.y, kBot);
  }

}


Bot::Move_ Bot::Minimax(Board* board, int player) {
  // check for game end
  switch(board->CheckVictory()) {
    case kUser: {
      return Move_(-1);
    }
    case kBot: {
      return Move_(1);
    }
    case kTie: {
      return Move_(0);
    }
    case 0: {
      break;
    }
    default: {
      exit(1);
    }
  }

  // create vector for moves
  std::vector<Move_>* moves = new std::vector<Move_>;

  // for each cell in the board, do move and call again using the other player
  for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++)
      {
        // if unused, do move
        if(board->GetCell(j, i) == kUnused) {  
          board->SetCell(j, i, player);
          Move_ move(j,i);

          // if we played as bot, we play next as user and vice versa
          if(player == kBot) {
              move.score = Minimax(board, kUser).score;
          } else {
              move.score = Minimax(board, kBot).score;
          }

          // pushing move to vector and resetting cell 
          moves->push_back(move);
          board->SetCell(j, i, kUnused);
        }
      }
  }

  // finding best move
  moves->shrink_to_fit();
  int best_move = 0;
  // if player is bot we are finding the move with largest score, if it is user we find the move with lowest score
  if(player == kBot) {
    int best_score = -1000000;
    for(int i = 0; i < (int)moves->size(); i++) {
      if((*moves)[i].score > best_score) {
        best_move = i;
        best_score = (*moves)[i].score;
      }
    }
  } else {
    int best_score = 1000000;
    for(int i = 0; i < (int)moves->size(); i++) {
      if((*moves)[i].score < best_score) {
        best_move = i;
        best_score = (*moves)[i].score;
      }
    }
  }
    
  // Retrieving best move from vector
  Move_ ret = (*moves)[best_move];
  // freeing used memory
  delete moves; 
  return ret;
}

void Bot::DoRandom(Board* board){
  int x;
  int y;
  
  // generate random x and y until hitting a clear spot
  do{
      x = rand() % 2;
      y = rand() % 2;
  } while(board->GetCell(x,y) != kUnused);
  board->SetCell(x, y, kBot);
}