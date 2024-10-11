/**
 * @file stem/inc/util/node/op_node/bin_node/Asterisk.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 10/2/2024
 */
#pragma once

#include <memory>
#include <iostream>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "ValueNode.hpp"
#include "UnaMinus.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"

namespace stem
{
  struct Asterisk : public BinOpNode
  {
    Asterisk(Token &tok_top);
    Asterisk(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Asterisk(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    bool interpret() override;
  };
}
