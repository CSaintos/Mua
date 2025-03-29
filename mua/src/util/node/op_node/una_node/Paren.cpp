#include "Paren.hpp"

using namespace std;
using namespace mua;

Paren::Paren(INodeFactory *node_factory, Token &tok_op)
  : UnaOpNode(tok_op)
{
  this->node_factory = node_factory;
}

Paren::Paren(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

Paren::Paren(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{
  this->node_factory = node_factory;
}

string Paren::to_repr()
{
  return "(" + node->to_repr() + ")";
}

bool Paren::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  if (!node->isLeaf())
  {
    change = node->interpret(flags);
  }
  else if (parent->tok.type != TokenType::ADJACENT)
  {
    NodeUtils::replaceNode(this, node);
    change = true;
  }
  return change;
}

unique_ptr<Node> Paren::copy()
{
  unique_ptr<Node> node_copy = node->copy();
  //return std::make_unique<Paren>(tok, node_copy);
  return node_factory->produceNode(tok, node_copy);
}
