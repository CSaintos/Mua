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
  return false;
}
