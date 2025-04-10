#include "node_state/Semicolon.hpp"

using namespace std;
using namespace mua;

string Semicolon::to_repr()
{
  return child->to_repr() + ";";
}

bool Semicolon::interpret(const unordered_set<InterpretType> &flags)
{
  return child->interpret(flags);
}
