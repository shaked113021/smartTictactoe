#pragma once
#include "tictactoe/Move.h"

namespace tictactoe {
namespace botstrategies {

class IStrategy
{
  public:
    virtual Move GenerateMove() = 0;
    virtual ~IStrategy() {};
};
}
}