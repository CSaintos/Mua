/**
 * @file stem/inc/util/node/op_node/bin_node/BinMinus.hpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 10/1/2024
 */
#pragma once

#include <memory>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "BinOpNode.hpp"
#include "UnaMinus.hpp"
#include "NodeUtils.hpp"
#include "NumberUtils.hpp"

namespace stem
{
  struct BinMinus : public BinOpNode
  {
    BinMinus(Token &tok_op);
    BinMinus(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    BinMinus(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);
    bool interpret() override;
  };
}
