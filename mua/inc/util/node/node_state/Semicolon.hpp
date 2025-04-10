#pragma once

#include <memory>
#include <unordered_set>

#include "Token.hpp"
#include "Node.hpp"
#include "InterpretType.hpp"
#include "UnaOpState.hpp"

namespace mua
{
  class Semicolon : public UnaOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
