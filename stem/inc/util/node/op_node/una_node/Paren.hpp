/**
 * @file stem/inc/util/node/op_node/una_node/Paren.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 10/16/2024
 */

#pragma once

#include <memory>
#include <unordered_set>

#include "Token.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "InterpretType.hpp"

namespace stem
{
  struct Paren : public UnaOpNode
  {
    Paren(Token &tok_op);
    Paren(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    Paren(Token &tok_op, std::unique_ptr<Node> &node);
    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
