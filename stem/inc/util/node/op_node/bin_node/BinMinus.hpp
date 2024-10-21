/**
 * @file stem/inc/util/node/op_node/bin_node/BinMinus.hpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 10/1/2024
 */
#pragma once

#include <memory>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "BinOpNode.hpp"
#include "BinPlus.hpp"
#include "UnaOpNode.hpp"
#include "UnaMinus.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"

namespace stem
{
  struct BinMinus : public BinOpNode
  {
    BinMinus(Token &tok_op);
    BinMinus(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    BinMinus(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
