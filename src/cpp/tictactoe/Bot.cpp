#include "../../include/tictactoe/Bot.h"
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <memory>

using namespace tictactoe;

// getting board and victory checker in constractor
Bot::Bot(Board* board, VictoryChecker* victory_checker) : board_(board), victory_checker_(victory_checker) {}

void Bot::DoMove() {
  // if this is first move, we don't need to run minimax evaluation on board
  if (this->is_first_) {
    this->DoRandom();
    this->is_first_ = false;
  } else {
    Move_ move = Minimax(kBot);
    this->board_->SetCell(move.x, move.y, kBot);
  }

}


Bot::Move_ Bot::Minimax(int player) {
  // check for game end
  switch(this->victory_checker_->Check()) {
    case kUser: {
      return Move_(kUserWinScore);
    }
    case kBot: {
      return Move_(kBotWinScore);
    }
    case kTie: {
      return Move_(kTieScore);
    }
    case kGamePending: {
      break;
    }
    default: {
      exit(1);
    }
  }

  // create vector for moves, using unique pointer for memory management
  std::unique_ptr<std::vector<Move_>> moves{new std::vector<Move_>};

  // for each cell in the board, do move and call again using the other player
  for(auto i = 0; i < kRowAndCollSize; ++i) {
    for(auto j = 0; j < kRowAndCollSize; ++j) {
      // if unused, do move
      if(this->board_->GetCell(j, i) == kUnused) {  
        this->board_->SetCell(j, i, player);
        Move_ move(j,i);

        // if we played as bot, we play next as user and vice versa
        if(player == kBot) {
          move.score = Minimax(kUser).score;
        } else {
          move.score = Minimax(kBot).score;
        }

        // pushing move to vector and resetting cell 
        moves.get()->push_back(move);
        this->board_->SetCell(j, i, kUnused);
      }
    }
  }

  // finding best move
  moves->shrink_to_fit();
  int moves_size = (int)moves->size();
  int best_move_index = 0;
  // if player is bot we are finding the move with largest score, if it is user we find the move with lowest score
  if(player == kBot) {
    int best_score = -1000000;
    for(auto i = 0; i < moves_size; ++i) {
      if((*moves)[i].score > best_score) {
        best_move_index = i;
        best_score = (*moves)[i].score;
      }
    }
  } else {
    int best_score = 1000000;
    for(auto i = 0; i < moves_size; ++i) {
      if((*moves)[i].score < best_score) {
        best_move_index = i;
        best_score = (*moves)[i].score;
      }
    }
  }
    
  // Retrieving best move from vector
  Move_ best_move = (*moves)[best_move_index];
  return best_move;
}

void Bot::DoRandom(){
  int x;
  int y;
  
  // generate random x and y until hitting a clear spot
  do{
    x = rand() % (kRowAndCollSize - 1);
    y = rand() % (kRowAndCollSize - 1);
  } while(this->board_->GetCell(x,y) != kUnused);
  this->board_->SetCell(x, y, kBot);
}