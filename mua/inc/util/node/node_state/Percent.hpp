#pragma once

#include <memory>
#include <iostream>
#include <cmath>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "NodeType.hpp"
#include "UnaOpNode.hpp"
#include "BinOpNode.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"
#include "BinOpState.hpp"

namespace mua
{
  class Percent : public BinOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
