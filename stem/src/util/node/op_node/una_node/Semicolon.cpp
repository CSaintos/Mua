#include "Semicolon.hpp"

using namespace std;
using namespace stem;

Semicolon::Semicolon(Token &tok_op)
  : UnaOpNode(tok_op)
{}

Semicolon::Semicolon(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

Semicolon::Semicolon(Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{}

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
  return std::make_unique<Semicolon>(tok, node_copy);
}
