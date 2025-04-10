#pragma once

#include <memory>

#include "Token.hpp"
#include "Node.hpp"
#include "InterpretType.hpp"
#include "UnaOpState.hpp"

namespace mua
{
  class Let : public UnaOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
