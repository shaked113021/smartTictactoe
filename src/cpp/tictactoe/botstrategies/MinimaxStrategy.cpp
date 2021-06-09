#include "tictactoe/botstrategies/MinimaxStrategy.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

using namespace tictactoe;
using namespace tictactoe::botstrategies;

MinimaxStrategy::MinimaxStrategy(const Board* t_board, const VictoryChecker* t_victory_checker) : m_board((Board*)t_board), m_victory_checker((VictoryChecker*)t_victory_checker) {}

MinimaxStrategy::~MinimaxStrategy() {}

Move MinimaxStrategy::GenerateMove()
{
  return Max();
}

Move MinimaxStrategy::Max() const
{
  // check for game end
  switch(this->m_victory_checker->Check())
  {
    case kUser:
    {
      // if user won, return negative score
      return Move(kUserWinScore);
    }
    case kBot:
    {
      // if bot won return positive score
      return Move(kBotWinScore);
    }
    case kTie:
    {
      // if tie return 0
      return Move(kTieScore);
    }
    case kGamePending:
    {
      // if game pending continue
      break;
    }
    default:
    {
      // if default, not a valid return value, probably a result of a stack overflow
      std::cout << "return value of victory checker was not valid, check for stack overflow\n";
      exit(1);
    }
  }

  // create vector for moves, using unique pointer for memory management
  std::unique_ptr<std::vector<Move>> moves(new std::vector<Move>);

  // for each cell in the board, do move and call min
  for(size_t y = 0; y < kRowAndCollSize; ++y)
  {
    for(size_t x = 0; x < kRowAndCollSize; ++x)
    {
      // if unused, do move
      if(this->m_board->GetCell(x, y) == kUnused)
      {
        // do move  
        this->m_board->SetCell(x, y, kBot);
        Move move(x,y);
        // Play as Min next
        move.score = Min().score;

        // pushing move to vector and resetting cell 
        moves.get()->push_back(move);
        this->m_board->SetCell(x, y, kUnused);
      }
    }
  }

  // shrinking vector
  moves->shrink_to_fit();

  // find best score
  int max_score = moves->at(0).score;
  int max_score_index = 0;
  size_t size = moves->size();

  // running on entire vector trying to find max score move
  for (size_t i = 1; i < size; ++i)
  {
    int current_score = moves->at(i).score;
    if (current_score > max_score)
    {
      max_score = current_score;
      max_score_index = i;
    }
  }

  return moves->at(max_score_index);
}

Move MinimaxStrategy::Min() const
{
  // check for game end
  switch(this->m_victory_checker->Check())
  {
    case kUser:
    {
      // if user won, return negative score
      return Move(kUserWinScore);
    }
    case kBot:
    {
      // if bot won return positive score
      return Move(kBotWinScore);
    }
    case kTie:
    {
      // if tie return 0
      return Move(kTieScore);
    }
    case kGamePending:
    {
      // if game pending continue
      break;
    }
    default:
    {
      // if default, not a valid return value, probably a result of a stack overflow
      std::cout << "return value of victory checker was not valid, check for stack overflow";
      exit(1);
    }
  }

  std::unique_ptr<std::vector<Move>> moves(new std::vector<Move>);

  // for each cell in the board, do move and call max
  for(size_t y = 0; y < kRowAndCollSize; ++y)
  {
    for(size_t x = 0; x < kRowAndCollSize; ++x)
    {
      // if unused, do move
      if(this->m_board->GetCell(x, y) == kUnused)
      {  
        this->m_board->SetCell(x, y, kUser);
        Move move(x,y);
        // Play as Max next
        move.score = Max().score;

        // pushing move to vector and resetting cell 
        moves.get()->push_back(move);
        this->m_board->SetCell(x, y, kUnused);
      }
    }
  }

  // shrinking vector
  moves->shrink_to_fit();

  // find best score
  int min_score = moves->at(0).score;
  int min_score_index = 0;
  size_t size = moves->size();

  // running on entire vector trying to find min score move
  for (size_t i = 1; i < size; ++i)
  {
    int current_score = moves->at(i).score;
    if (current_score < min_score)
    {
      min_score = current_score;
      min_score_index = i;
    }
  }

  return moves->at(min_score_index);
}