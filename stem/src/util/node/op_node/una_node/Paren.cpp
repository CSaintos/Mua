#include "Paren.hpp"

using namespace std;
using namespace stem;

Paren::Paren(Token &tok_op)
  : UnaOpNode(tok_op)
{}

Paren::Paren(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

Paren::Paren(Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{}

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
  return std::make_unique<Paren>(tok, node_copy);
}
