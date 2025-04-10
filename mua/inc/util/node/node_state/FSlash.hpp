#pragma once

#include <memory>
#include <iostream>
#include <numeric>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "NodeType.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"
#include "BinOpState.hpp"

namespace mua
{
  class FSlash : public BinOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
