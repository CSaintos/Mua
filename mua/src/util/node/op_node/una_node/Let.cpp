#include "Let.hpp"

using namespace std;
using namespace mua;

Let::Let(INodeFactory *node_factory, Token &tok_op)
  : UnaOpNode(tok_op)
{
  this->node_factory = node_factory;
}

Let::Let(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

Let::Let(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{
  this->node_factory = node_factory;
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

unique_ptr<Node> Let::copy()
{
  //probably not safe code
  //return std::make_unique<Let>(tok, (unique_ptr<Node> &)*node->copy());
  unique_ptr<Node> node_copy = node->copy();
  return node_factory->produceNode(tok, node_copy);
}
