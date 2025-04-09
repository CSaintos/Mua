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
#include "INodeFactory.hpp"

namespace mua
{
  struct FSlash : public BinOpNode
  {
    FSlash(INodeFactory *node_factory, Token &tok_op);
    FSlash(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    FSlash(INodeFactory *node_factory, std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
