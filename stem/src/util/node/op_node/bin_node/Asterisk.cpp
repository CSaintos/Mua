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

bool Asterisk::interpret()
{
  if (node_left->isLeaf() && node_right->isLeaf())
  {
    if (node_left->tok.type == TokenType::DIGIT &&
      node_right->tok.type == TokenType::DIGIT)
    {
      unique_ptr<Node> res_node;
      double lhs = std::stod(node_left->tok.lexemes);
      double rhs = std::stod(node_right->tok.lexemes);
      double result = lhs * rhs;

      string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));

      Token res_tok;
      res_tok.lexemes = result_str;
      res_tok.type = TokenType::DIGIT;

      res_node = std::make_unique<ValueNode>(res_tok);

      NodeUtils::replaceNode(this, res_node);
      return true;
    }
  }
  else if (!node_left->isLeaf())
  {
    return node_left->interpret();
  }
  else if (!node_right->isLeaf())
  {
    return node_right->interpret();
  }
  return false;
}
