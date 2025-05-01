#pragma once

#include <memory>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"
#include "Node.hpp"
#include "NodeUtils.hpp"
#include "InterpretType.hpp"
#include "UnaOpState.hpp"

namespace mua
{
  class UnaMinus : public UnaOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
