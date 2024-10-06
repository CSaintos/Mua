/*
 * @file stem/inc/util/node/op_node/bin_node/Percent.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 10/6/2024
 */
#pragma once

#include <memory>
#include <iostream>
#include <cmath>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "BinOpNode.hpp"
#include "NumberUtils.hpp"
#include "NodeUtils.hpp"

namespace stem
{
  struct Percent : public BinOpNode
  {
    Percent(Token &tok_op);
    Percent(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Percent(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    bool interpret() override;
  };
}
