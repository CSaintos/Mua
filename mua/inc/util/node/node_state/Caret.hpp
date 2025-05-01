#pragma once

#include <memory>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <list>
#include <map>

#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"
#include "BinOpState.hpp"

namespace mua
{
  class Caret : public BinOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
