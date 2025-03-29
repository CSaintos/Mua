/**
 * @file mua/inc/util/node/op_node/bin_node/BinPlus.hpp
 * @author Christian Santos
 * @version 1.0.5
 * @date 1/2/2025
 */

#pragma once

#include <memory>
#include <iostream>
#include <unordered_set>

#include "TokenType.hpp"
#include "Token.hpp"
#include "NodeType.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "BinOpNode.hpp"
#include "FSlash.hpp"
#include "BinMinus.hpp"
#include "UnaOpNode.hpp"
#include "UnaMinus.hpp"
#include "Paren.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct BinPlus : public BinOpNode
  {
    BinPlus(INodeFactory *node_factory, Token &tok_op);
    BinPlus(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    BinPlus(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
    std::unique_ptr<Node> copy() override;
  };
}
