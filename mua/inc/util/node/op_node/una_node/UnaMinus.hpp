/**
 * @file mua/inc/util/node/op_node/una_node/UnaMinus.hpp
 * @author Christian Santos
 * @version 1.0.2
 * @date 10/12/2024
 */
#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "NumberUtils.hpp"
#include "InterpretType.hpp"

namespace mua
{
  struct UnaMinus : public UnaOpNode
  {
    UnaMinus(Token &tok_op);
    UnaMinus(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    UnaMinus(Token &tok_op, std::unique_ptr<Node> &node);
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags) override;
    std::unique_ptr<Node> copy() override;
  };
}
