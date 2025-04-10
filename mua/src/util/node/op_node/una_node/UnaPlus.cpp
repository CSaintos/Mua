#include "op_node/una_node/UnaPlus.hpp"

using namespace std;
using namespace mua;

UnaPlus::UnaPlus(INodeFactory *node_factory, Token &tok_op)
  : UnaOpNode(node_factory, tok_op)
{
}

UnaPlus::UnaPlus(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : UnaOpNode(node_op, node)
{}

UnaPlus::UnaPlus(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node)
  : UnaOpNode(node_factory, tok_op, node)
{
}

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
    change = node->interpret(flags);
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

  res_node = node_factory->produceNode(res_tok);

  if (is_negative)
  {
    res_node = node_factory->produceNode(TokenType::MINUS, res_node);
  }

  if (res_node->to_repr() != this->to_repr())
  {
    NodeUtils::replaceNode(this, res_node);
    change = true;
  }

  return change;
}

