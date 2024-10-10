/**
 * @file stem/inc/util/node/op_node/una_node/Semicolon.hpp
 * @author Christian Santos
 * @version 1.0.2
 * @date 10/1/2024
 */

#pragma once

#include <memory>
#include <string>

#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "Token.hpp"

namespace stem
{
  struct Semicolon : public UnaOpNode
  {
    Semicolon(Token &tok_op);
    Semicolon(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    Semicolon(Token &tok_op, std::unique_ptr<Node> &node);
    std::string to_repr() override;
    bool interpret() override;
  };
}
