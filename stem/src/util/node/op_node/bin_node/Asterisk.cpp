#include "Asterisk.hpp"

using namespace std;
using namespace stem;

Asterisk::Asterisk(Token &tok_op)
  : BinOpNode(tok_op)
{}

Asterisk::Asterisk(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

Asterisk::Asterisk(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

bool Asterisk::interpret(const unordered_set<InterpretType> &flags)
{
  unique_ptr<Node> res_node;
  string left_str;
  string right_str;
  bool left_change = false;
  bool right_change = false;

  if (!node_left->isLeaf())
  {
    left_change = node_left->interpret();
  }
  if (!node_right->isLeaf())
  {
    right_change = node_right->interpret();
  }
  if (left_change || right_change)
  {
    return true;
  }

  left_str = node_left->to_repr();
  right_str = node_right->to_repr();

  double lhs = std::stod(left_str);
  double rhs = std::stod(right_str);
  double result = lhs * rhs;
  bool is_negative = false;
  
  if (result < 0)
  {
    result = result * -1;
    is_negative = true;
  }

  string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));

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

  NodeUtils::replaceNode(this, res_node);
  return true;
}
