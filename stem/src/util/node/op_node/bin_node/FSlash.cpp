#include "FSlash.hpp"

using namespace std;
using namespace stem;

FSlash::FSlash(Token &tok_op)
  : BinOpNode(tok_op)
{}

FSlash::FSlash(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

FSlash::FSlash(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

bool FSlash::interpret()
{
  if (node_left->isLeaf() && node_right->isLeaf())
  {
    if (node_left->tok.type == TokenType::DIGIT &&
    node_right->tok.type == TokenType::DIGIT)
    {
      unique_ptr<Node> res_node;
      unique_ptr<Node> lhs_node = NumberUtils::fractionalize(node_left->tok.lexemes);
      unique_ptr<Node> rhs_node = NumberUtils::fractionalize(node_right->tok.lexemes);

      if (lhs_node->isLeaf() && rhs_node->isLeaf())
      {
        int lhs = std::stod(lhs_node->tok.lexemes);       
        int rhs = std::stod(rhs_node->tok.lexemes);
        int gcd = std::gcd(lhs, rhs);
        if (gcd == 1)
        {
          double result = double(lhs) / double(rhs);
          string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));
          Token res_tok;
          res_tok.type = TokenType::DIGIT;
          res_tok.lexemes = result_str;
          res_node = std::make_unique<ValueNode>(res_tok);
          NodeUtils::replaceNode(this, res_node);
        }
        else
        {
          lhs = lhs / gcd;
          rhs = rhs / gcd;
          lhs_node->tok.lexemes = std::to_string(lhs);
          rhs_node->tok.lexemes = std::to_string(rhs);
          node_left = std::move(lhs_node);
          node_right = std::move(rhs_node);
        }
      }
      else 
      {
        if (!lhs_node->isLeaf())
        {
          node_left = std::move(lhs_node);
        }
        if (!rhs_node->isLeaf())
        {
          node_right = std::move(rhs_node);
        }
      }

      return true;
      //int gcd = std::gcd(lhs, rhs);
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
