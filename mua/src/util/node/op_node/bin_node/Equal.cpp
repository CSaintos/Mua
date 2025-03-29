#include "Equal.hpp"

using namespace std;
using namespace mua;

Equal::Equal(INodeFactory *node_factory, Token &tok_op)
  : BinOpNode(tok_op)
{
  this->node_factory = node_factory;
}

Equal::Equal(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

Equal::Equal(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

bool Equal::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  return false;
}

unique_ptr<Node> Equal::copy()
{
  unique_ptr<Node> lhs_node = node_left->copy();
  unique_ptr<Node> rhs_node = node_right->copy();
  return std::make_unique<Equal>(lhs_node, tok, rhs_node);
}
