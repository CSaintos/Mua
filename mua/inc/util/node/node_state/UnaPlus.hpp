#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"
#include "Node.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"
#include "UnaOpState.hpp"
#include "UnaOpNode.hpp"
#include "BinOpNode.hpp"

namespace mua
{
  class UnaPlus : public UnaOpState
  {
  public:
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
