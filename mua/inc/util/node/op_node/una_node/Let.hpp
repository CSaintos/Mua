#pragma once

#include <memory>

#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "Token.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct Let : public UnaOpNode
  {
    Let(INodeFactory *node_factory, Token &tok_op);
    Let(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    Let(INodeFactory *node_factory, Token &tok_op, std::unique_ptr<Node> &node);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
