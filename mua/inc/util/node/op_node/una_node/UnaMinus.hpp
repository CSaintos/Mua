#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "NodeUtils.hpp"
#include "InterpretType.hpp"
#include "INodeFactory.hpp"

namespace mua
{
  struct UnaMinus : public UnaOpNode
  {
    UnaMinus(INodeFactory *node_factory, Token &tok_op);
    UnaMinus(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    UnaMinus(INodeFactory *node_factory, Token &tok_op, std::unique_ptr<Node> &node);

    std::string to_repr() override;
    bool interpret(const std::unordered_set<InterpretType> &flags) override;
  };
}
