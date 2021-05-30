#pragma once

namespace tictactoe {
namespace botstrategies {

  class Strategy {
    public:
      virtual void DoMove() = 0;
  };
}
}