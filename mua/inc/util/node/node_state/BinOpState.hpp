#pragma once

#include <string>
#include <unordered_set>
#include <memory>

#include "Token.hpp"
#include "Node.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "NumberUtils.hpp"
#include "INodeState.hpp"
#include "INodeFactory.hpp"
#include "InterpretType.hpp"

namespace mua
{
  class BinOpState : public INodeState
  {
  private:
    void extractChildData
    (
      Node *in_child,
      std::unique_ptr<Node> &out_child,
      std::unique_ptr<Node> &numerator,
      std::unique_ptr<Node> &denominator,
      bool &is_minus,
      bool &removable_paren,
      bool &is_paren,
      const bool &is_leaf
    );
  protected:
    BinOpNode *node;
    Node *node_left;
    Node *node_right;
    INodeFactory *node_factory;
    Token *tok;
    
    void extractNodeChildrenData
    (
      std::unique_ptr<Node> &lhs_node,
      std::unique_ptr<Node> &rhs_node,
      std::unique_ptr<Node> &left_numerator,
      std::unique_ptr<Node> &left_denominator,
      std::unique_ptr<Node> &right_numerator,
      std::unique_ptr<Node> &right_denominator,
      bool &is_left_minus,
      bool &is_right_minus,
      bool &removable_right_paren,
      bool &is_lhs_paren,
      const bool &is_left_leaf,
      const bool &is_right_leaf
    );
  public:
    void setContext(Node *node) override;
  };
}
