#pragma once

#include <memory>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "InterpretType.hpp"
#include "UnaOpState.hpp"
#include "UnaOpNode.hpp"
#include "BinOpNode.hpp"

namespace mua
{
  class Semicolon : public UnaOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
