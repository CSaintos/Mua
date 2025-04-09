#pragma once

#include <memory>
#include <unordered_set>

#include "TokenType.hpp"
#include "Token.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "InterpretType.hpp"
#include "NodeUtils.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct Paren : public UnaOpNode
  {
    Paren(INodeFactory *node_factory, Token &tok_op);
    Paren(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    Paren(INodeFactory *node_factory, Token &tok_op, std::unique_ptr<Node> &node);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;
  };
}
