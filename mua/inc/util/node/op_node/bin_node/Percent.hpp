/*
 * @file mua/inc/util/node/op_node/bin_node/Percent.hpp
 * @author Christian Santos
 * @version 1.0.2
 * @date 1/2/2025
 */
#pragma once

#include <memory>
#include <iostream>
#include <cmath>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "BinOpNode.hpp"
#include "NumberUtils.hpp"
#include "NodeUtils.hpp"
#include "InterpretType.hpp"

namespace mua
{
  struct Percent : public BinOpNode
  {
    Percent(Token &tok_op);
    Percent(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Percent(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
    std::unique_ptr<Node> copy() override;
  };
}
