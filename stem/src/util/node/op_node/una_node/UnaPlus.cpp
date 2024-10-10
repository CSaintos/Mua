#include "UnaPlus.hpp"

using namespace std;
using namespace stem;

UnaPlus::UnaPlus(Token &tok_op)
  : UnaOpNode(tok_op)
{}

UnaPlus::UnaPlus(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

UnaPlus::UnaPlus(Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{}

string UnaPlus::to_repr()
{
  return "+" + node->to_repr();
}

bool UnaPlus::interpret()
{
  return node->interpret();
}
