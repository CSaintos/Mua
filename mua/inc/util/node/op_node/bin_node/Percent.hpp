#pragma once

#include <memory>
#include <iostream>
#include <cmath>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "NumberUtils.hpp"
#include "NodeUtils.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct Percent : public BinOpNode
  {
    Percent(INodeFactory *node_factory, Token &tok_op);
    Percent(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Percent(INodeFactory *node_factory, std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
