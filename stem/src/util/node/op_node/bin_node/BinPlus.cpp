#include "BinPlus.hpp"
#include "NodeUtils.hpp"

using namespace std;
using namespace stem;

BinPlus::BinPlus(Token &tok_op)
  : BinOpNode(tok_op) 
{}

BinPlus::BinPlus(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

BinPlus::BinPlus(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

bool BinPlus::interpret() 
{
  if (node_left->isLeaf() && node_right->isLeaf())
  {
    if (node_left->tok.type == TokenType::DIGIT &&
      node_right->tok.type == TokenType::DIGIT)
    {
      double lhs = std::stod(node_left->tok.lexemes);
      double rhs = std::stod(node_right->tok.lexemes);
      double result = lhs + rhs;

      string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));

      Token res_tok;
      res_tok.lexemes = result_str;
      res_tok.type = TokenType::DIGIT;

      unique_ptr<Node> res_node = std::make_unique<ValueNode>(res_tok);

      NodeUtils::replaceNode(this, res_node);
      return true;
    }
  }
  else
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
    if (!left_change)
    {
      left_str = node_left->to_repr();
    }
    if (!right_change)
    {
      right_str = node_right->to_repr();
    }

    double lhs = std::stod(left_str);
    double rhs = std::stod(right_str);
    double result = lhs + rhs;
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
  
  return false;
}
