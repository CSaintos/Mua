#pragma once

#include <memory>
#include <iostream>
#include <unordered_set>

#include "Token.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "InterpretType.hpp"
#include "BinOpState.hpp"

namespace mua
{
  class Equal : public BinOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
