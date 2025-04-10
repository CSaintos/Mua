#pragma once

#include <memory>
#include <unordered_set>

#include "TokenType.hpp"
#include "Token.hpp"
#include "Node.hpp"
#include "InterpretType.hpp"
#include "NodeUtils.hpp"
#include "UnaOpState.hpp"

namespace mua
{
  class Paren : public UnaOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
