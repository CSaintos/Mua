#include "op_node/una_node/Semicolon.hpp"

using namespace std;
using namespace mua;

Semicolon::Semicolon(INodeFactory *node_factory, Token &tok_op)
  : UnaOpNode(node_factory, tok_op)
{
}

Semicolon::Semicolon(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

Semicolon::Semicolon(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(node_factory, tok_op, node)
{
}

string Semicolon::to_repr()
{
  return node->to_repr() + ";";
}

bool Semicolon::interpret(const unordered_set<InterpretType> &flags)
{
  return node->interpret(flags);
}
