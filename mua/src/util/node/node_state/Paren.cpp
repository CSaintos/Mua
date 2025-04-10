#include "node_state/Paren.hpp"

using namespace std;
using namespace mua;

string Paren::to_repr()
{
  return "(" + child->to_repr() + ")";
}

bool Paren::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  if (!child->isLeaf())
  {
    change = child->interpret(flags);
  }
  else if (node->parent->tok.type != TokenType::ADJACENT)
  {
    NodeUtils::replaceNode(node, node->node);
    change = true;
  }
  return change;
}

