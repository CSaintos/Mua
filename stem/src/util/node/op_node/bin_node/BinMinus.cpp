#include "BinMinus.hpp"

using namespace std;
using namespace stem;

BinMinus::BinMinus(Token &tok_op)
  : BinOpNode(tok_op)
{}

BinMinus::BinMinus(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

BinMinus::BinMinus(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

void BinMinus::interpret()
{
  if (node_left->isLeaf() && node_right->isLeaf())
  {
    if (node_left->tok.type == TokenType::DIGIT &&
      node_right->tok.type == TokenType::DIGIT)
    {
      unique_ptr<Node> res_node;
      double lhs = std::stod(node_left->tok.lexemes);
      double rhs = std::stod(node_right->tok.lexemes);
      double result = lhs - rhs;
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
        res_node = std::make_unique<UnaOpNode>(minus_tok, res_node);
      }

      NodeUtils::replaceNode(this, res_node);
    }
  }
}
