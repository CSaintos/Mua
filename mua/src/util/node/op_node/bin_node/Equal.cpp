#include "op_node/bin_node/Equal.hpp"

using namespace std;
using namespace mua;

Equal::Equal(INodeFactory *node_factory, Token &tok_op)
  : BinOpNode(node_factory, tok_op)
{
}

Equal::Equal(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

Equal::Equal(INodeFactory *node_factory, unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_factory, node_left, tok_op, node_right)
{
}

bool Equal::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  return false;
}

