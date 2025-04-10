#include "Node.hpp"

using namespace std;
using namespace mua;

bool Node::isExclusiveParent()
{
  return (!isLeaf() && !hasGrandchildren());
}

string Node::to_repr()
{
  return state->to_repr();
}

bool Node::interpret(const unordered_set<InterpretType> &flags)
{
  return state->interpret(flags);
}
