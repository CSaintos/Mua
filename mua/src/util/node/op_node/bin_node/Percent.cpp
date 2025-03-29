#include "Percent.hpp"

using namespace std;
using namespace mua;

Percent::Percent(INodeFactory *node_factory, Token &tok_op)
  : BinOpNode(tok_op)
{
  this->node_factory = node_factory;
}

Percent::Percent(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

Percent::Percent(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

string Percent::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return "%";
  }
  return node_left->to_repr() + "%" + node_right->to_repr();
}

bool Percent::interpret(const unordered_set<InterpretType> &flags)
{
  if (node_left->isLeaf() && node_right->isLeaf())
  {
    if (node_left->tok.type == TokenType::DIGIT &&
    node_right->tok.type == TokenType::DIGIT)
    {
      double lhs = std::stod(node_left->tok.lexemes);
      double rhs = std::stod(node_right->tok.lexemes);
      double result = std::fmod(lhs, rhs);

      string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));

      Token res_tok;
      res_tok.lexemes = result_str;
      res_tok.type = TokenType::DIGIT;

      unique_ptr<Node> res_node = std::make_unique<ValueNode>(res_tok);

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

unique_ptr<Node> Percent::copy()
{
  unique_ptr<Node> lhs_node = node_left->copy();
  unique_ptr<Node> rhs_node = node_right->copy();
  return std::make_unique<Percent>(lhs_node, tok, rhs_node);
}
