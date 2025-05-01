#include "node_state/UnaPlus.hpp"

using namespace std;
using namespace mua;

string UnaPlus::to_repr()
{
  return "+" + child->to_repr();
}

bool UnaPlus::interpret(const unordered_set<InterpretType> &flags)
{
  unique_ptr<Node> res_node;
  string str_repr;
  bool change = false;

  if (!child->isLeaf())
  {
    change = child->interpret(flags);
  }
  if (change) return true;

  str_repr = child->to_repr();

  double signed_value = std::stod(str_repr);
  bool is_negative = false;

  if (signed_value < 0)
  {
    signed_value = signed_value * -1;
    is_negative = true;
  }

  string result_str = NumberUtils::stripTrailingZeros(std::to_string(signed_value));

  Token res_tok;
  res_tok.lexemes = result_str;
  res_tok.type = TokenType::DIGIT;

  res_node = node_factory->produceNode(res_tok);

  if (is_negative)
  {
    res_node = node_factory->produceNode(TokenType::MINUS, res_node);
  }

  if (res_node->to_repr() != this->to_repr())
  {
    NodeUtils::replaceNode(node, res_node);
    change = true;
  }

  return change;
}

