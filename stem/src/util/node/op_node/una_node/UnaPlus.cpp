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

bool UnaPlus::interpret(const unordered_set<InterpretType> &flags)
{
  unique_ptr<Node> res_node;
  string str_repr;
  bool change = false;

  if (!node->isLeaf())
  {
    change = node->interpret();
  }
  if (change) return true;

  str_repr = node->to_repr();

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

  res_node = std::make_unique<ValueNode>(res_tok);

  if (is_negative)
  {
    Token minus_tok;
    minus_tok.type = TokenType::MINUS;
    res_node = std::make_unique<UnaMinus>(minus_tok, res_node);
  }

  if (res_node->to_repr() != this->to_repr())
  {
    NodeUtils::replaceNode(this, res_node);
    change = true;
  }

  return change;
}

unique_ptr<Node> UnaPlus::copy()
{
  unique_ptr<Node> node_copy = node->copy();
  return std::make_unique<UnaPlus>(tok, node_copy);
}
