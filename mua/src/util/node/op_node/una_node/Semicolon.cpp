#include "Semicolon.hpp"

using namespace std;
using namespace mua;

Semicolon::Semicolon(INodeFactory *node_factory, Token &tok_op)
  : UnaOpNode(tok_op)
{
  this->node_factory = node_factory;
}

Semicolon::Semicolon(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

Semicolon::Semicolon(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{
  this->node_factory = node_factory;
}

string Semicolon::to_repr()
{
  return node->to_repr() + ";";
}

bool Semicolon::interpret(const unordered_set<InterpretType> &flags)
{
  return node->interpret(flags);
}

unique_ptr<Node> Semicolon::copy()
{
  unique_ptr<Node> node_copy = node->copy();
  return node_factory->produceNode(tok, node_copy);
}
