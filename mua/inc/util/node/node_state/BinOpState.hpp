#pragma once

#include <string>
#include <unordered_set>

#include "Token.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "INodeState.hpp"
#include "INodeFactory.hpp"
#include "InterpretType.hpp"

namespace mua
{
  class BinOpState : public INodeState
  {
  protected:
    BinOpNode *node;
    Node *node_left;
    Node *node_right;
    INodeFactory *node_factory;
    Token *tok;
  public:
    void setContext(Node *node) override;
  };
}
