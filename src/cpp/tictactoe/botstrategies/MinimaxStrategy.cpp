#include "tictactoe/botstrategies/MinimaxStrategy.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

using namespace tictactoe;
using namespace tictactoe::botstrategies;

MinimaxStrategy::MinimaxStrategy(Board* board, VictoryChecker* victory_checker) : board_(board), victory_checker_(victory_checker) {}

MinimaxStrategy::~MinimaxStrategy() {}

Move MinimaxStrategy::GenerateMove() {
  return Max();
}

Move MinimaxStrategy::Max() const {
  // check for game end
  switch(this->victory_checker_->Check()) {
    case kUser: {
      // if user won, return negative score
      return Move(kUserWinScore);
    }
    case kBot: {
      // if bot won return positive score
      return Move(kBotWinScore);
    }
    case kTie: {
      // return 0
      return Move(kTieScore);
    }
    case kGamePending: {
      // if game pending continue
      break;
    }
    default: {
      // if default, not a valid return value, probably a result of a stack overflow
      std::cout << "return value of victory checker was not valid, check for stack overflow";
      exit(1);
    }
  }

  // create vector for moves, using unique pointer for memory management
  std::unique_ptr<std::vector<Move>> moves(new std::vector<Move>);

  // for each cell in the board, do move and call min
  for(auto y = 0; y < kRowAndCollSize; ++y) {
    for(auto x = 0; x < kRowAndCollSize; ++x) {
      // if unused, do move
      if(this->board_->GetCell(x, y) == kUnused) {  
        this->board_->SetCell(x, y, kBot);
        Move move(x,y);
        // Play as Min next
        move.score = Min().score;

        // pushing move to vector and resetting cell 
        moves.get()->push_back(move);
        this->board_->SetCell(x, y, kUnused);
      }
    }
  }

  // shrinking vector
  moves->shrink_to_fit();

  // find best score
  int max_score = moves->at(0).score;
  int max_score_index = 0;
  int size = moves->size();

  // running on entire vector trying to find max score move
  for (auto i = 1; i < size; ++i) {
    if (moves->at(i).score > max_score) {
      max_score = moves->at(i).score;
      max_score_index = i;
    }
  }

  return moves->at(max_score_index);
}

Move MinimaxStrategy::Min() const {
  // check for game end
  switch(this->victory_checker_->Check()) {
    case kUser: {
      // if user won, return negative score
      return Move(kUserWinScore);
    }
    case kBot: {
      // if bot won return positive score
      return Move(kBotWinScore);
    }
    case kTie: {
      // return 0
      return Move(kTieScore);
    }
    case kGamePending: {
      // if game pending continue
      break;
    }
    default: {
      // if default, not a valid return value, probably a result of a stack overflow
      std::cout << "return value of victory checker was not valid, check for stack overflow";
      exit(1);
    }
  }

  std::unique_ptr<std::vector<Move>> moves(new std::vector<Move>);

  // for each cell in the board, do move and call max
  for(auto y = 0; y < kRowAndCollSize; ++y) {
    for(auto x = 0; x < kRowAndCollSize; ++x) {
      // if unused, do move
      if(this->board_->GetCell(x, y) == kUnused) {  
        this->board_->SetCell(x, y, kUser);
        Move move(x,y);
        // Play as Max next
        move.score = Max().score;

        // pushing move to vector and resetting cell 
        moves.get()->push_back(move);
        this->board_->SetCell(x, y, kUnused);
      }
    }
  }

  // shrinking vector
  moves->shrink_to_fit();

  // find best score
  int min_score = moves->at(0).score;
  int min_score_index = 0;
  int size = moves->size();

  // running on entire vector trying to find max score move
  for (auto i = 1; i < size; ++i) {
    if (moves->at(i).score < min_score) {
      min_score = moves->at(i).score;
      min_score_index = i;
    }
  }

  return moves->at(min_score_index);
}