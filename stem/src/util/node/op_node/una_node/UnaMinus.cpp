#include "UnaMinus.hpp"

using namespace std;
using namespace stem;

UnaMinus::UnaMinus(Token &tok_op)
  : UnaOpNode(tok_op)
{}

UnaMinus::UnaMinus(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

UnaMinus::UnaMinus(Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(tok_op, node)
{}

string UnaMinus::to_repr()
{
  return "-" + node->to_repr();
}

bool UnaMinus::interpret()
{
  return node->interpret();
}
