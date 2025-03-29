/**
 * @file mua/inc/util/node/op_node/una_node/Let.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 11/14/2024
 */
#pragma once

#include <memory>

#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "Token.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct Let : public UnaOpNode
  {
    Let(INodeFactory *node_factory, Token &tok_op);
    Let(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    Let(Token &tok_op, std::unique_ptr<Node> &node);
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
    std::unique_ptr<Node> copy() override;
  };
}
