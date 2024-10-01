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

void Semicolon::interpret()
{
  node->interpret();
}
