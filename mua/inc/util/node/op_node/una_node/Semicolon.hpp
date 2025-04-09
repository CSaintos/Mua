#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "Token.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct Semicolon : public UnaOpNode
  {
    Semicolon(INodeFactory *node_factory, Token &tok_op);
    Semicolon(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    Semicolon(INodeFactory *node_factory, Token &tok_op, std::unique_ptr<Node> &node);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
