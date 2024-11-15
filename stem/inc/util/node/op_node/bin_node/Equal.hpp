/* 
 * @file stem/inc/util/node/op_node/bin_node/Equal.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 11/14/2024
 */
#pragma once

#include <memory>
#include <iostream>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "InterpretType.hpp"

namespace stem
{
  struct Equal : public BinOpNode
  {
    Equal(Token &tok_op);
    Equal(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Equal(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
    std::unique_ptr<Node> copy() override;
  };
}
