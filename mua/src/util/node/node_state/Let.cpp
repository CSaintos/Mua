#include "node_state/Let.hpp"

using namespace std;
using namespace mua;

string Let::to_repr()
{
  return "let " + child->to_repr();
}

bool Let::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  return change;
}

