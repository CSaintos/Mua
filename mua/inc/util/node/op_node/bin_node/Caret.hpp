/*
 * @file mua/inc/util/node/op_node/bin_node/Caret.hpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 10/12/2024
 */
#pragma once

#include <memory>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <list>
#include <map>

#include "Token.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct Caret : public BinOpNode
  {
    Caret(INodeFactory *node_factory, Token &tok_op);
    Caret(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    Caret(INodeFactory *node_factory, std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
    std::unique_ptr<Node> copy() override;
  };
}
