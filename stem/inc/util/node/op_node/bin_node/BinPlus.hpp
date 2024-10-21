/**
 * @file stem/inc/util/node/op_node/bin_node/BinPlus.hpp
 * @author Christian Santos
 * @version 1.0.4
 * @date 10/12/2024
 */

#pragma once

#include <memory>
#include <iostream>
#include <unordered_set>

#include "TokenType.hpp"
#include "Token.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "BinOpNode.hpp"
#include "BinMinus.hpp"
#include "UnaOpNode.hpp"
#include "UnaMinus.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"

namespace stem
{
  struct BinPlus : public BinOpNode
  {
    BinPlus(Token &tok_op);
    BinPlus(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    BinPlus(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
