#include "op_node/una_node/Let.hpp"

using namespace std;
using namespace mua;

Let::Let(INodeFactory *node_factory, Token &tok_op)
  : UnaOpNode(node_factory, tok_op)
{
}

Let::Let(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

Let::Let(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(node_factory, tok_op, node)
{
}

string Let::to_repr()
{
  return "let " + node->to_repr();
}

bool Let::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  return change;
}

