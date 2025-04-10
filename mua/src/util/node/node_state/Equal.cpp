#include "node_state/Equal.hpp"

using namespace std;
using namespace mua;

string Equal::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return "=";
  }
  return node_left->to_repr() + "=" + node_right->to_repr(); 
}

bool Equal::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  return false;
}

