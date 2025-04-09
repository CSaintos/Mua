#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "NumberUtils.hpp"
#include "NodeUtils.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct UnaPlus : public UnaOpNode
  {
    UnaPlus(INodeFactory *node_factory, Token &tok_op);
    UnaPlus(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    UnaPlus(INodeFactory *node_factory, Token &tok_op, std::unique_ptr<Node> &node);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
