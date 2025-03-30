/**
 * @file mua/inc/util/node/op_node/bin_node/Asterisk.hpp
 * @author Christian Santos
 * @version 1.0.2
 * @date 1/2/2025
 */
#pragma once

#include <memory>
#include <iostream>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct Asterisk : public BinOpNode
  {
    Asterisk(INodeFactory *node_factory, Token &tok_top);
    Asterisk(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Asterisk(INodeFactory *node_factory, std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
