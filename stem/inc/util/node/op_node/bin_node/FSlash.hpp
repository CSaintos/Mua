/*
 * @file stem/inc/util/node/op_node/bin_node/FSlash.hpp
 * @author Christian Santos
 * @version 1.0.4
 * @date 1/2/2025
 */

#pragma once

#include <memory>
#include <iostream>
#include <numeric>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "Asterisk.hpp"
#include "UnaOpNode.hpp"
#include "Paren.hpp"
#include "ValueNode.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"

namespace stem
{
  struct FSlash : public BinOpNode
  {
    bool is_const_fraction = false;
    FSlash(Token &tok_op);
    FSlash(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    FSlash(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
    std::unique_ptr<Node> copy() override;
  };
}
