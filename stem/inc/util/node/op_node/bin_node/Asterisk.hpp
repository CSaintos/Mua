/**
 * @file stem/inc/util/node/op_node/bin_node/Asterisk.hpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 10/12/2024
 */
#pragma once

#include <memory>
#include <iostream>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "ValueNode.hpp"
#include "UnaOpNode.hpp"
#include "UnaMinus.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"

namespace stem
{
  struct Asterisk : public BinOpNode
  {
    Asterisk(Token &tok_top);
    Asterisk(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Asterisk(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
    std::unique_ptr<Node> copy() override;
  };
}
