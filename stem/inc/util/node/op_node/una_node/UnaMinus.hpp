/**
 * @file stem/inc/util/node/op_node/una_node/UnaMinus.hpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 10/7/2024
 */
#pragma once

#include <memory>
#include <iostream>
#include <string>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"

namespace stem
{
  struct UnaMinus : public UnaOpNode
  {
    UnaMinus(Token &tok_op);
    UnaMinus(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    UnaMinus(Token &tok_op, std::unique_ptr<Node> &node);
    std::string to_repr() override;
    bool interpret() override;
  };
}
