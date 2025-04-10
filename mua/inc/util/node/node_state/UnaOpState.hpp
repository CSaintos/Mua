#pragma once

#include <string>
#include <unordered_set>

#include "Token.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "INodeState.hpp"
#include "INodeFactory.hpp"
#include "InterpretType.hpp"

namespace mua
{
  class UnaOpState : public INodeState
  {
  protected:
    UnaOpNode *node;
    Node *child;
    INodeFactory *node_factory;
    Token *tok;
  public:
    void setContext(Node *node) override;
  };
}
