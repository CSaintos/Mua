#include "BinPlus.hpp"

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

void BinPlus::interpret() 
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

      replaceNode(this, res_node);
    }
  }
}

void BinPlus::replaceNode(Node* to_replace, unique_ptr<Node> &replace_with)
{
  if (to_replace->parent->getType() == NodeType::BINARY_OPERATOR)
  {
    BinOpNode* parent = static_cast<BinOpNode*>(to_replace->parent);
    if (parent->node_left.get() == to_replace)
    {
      parent->node_left = std::move(replace_with);
    }
    else if (parent->node_right.get() == to_replace)
    {
      parent->node_right = std::move(replace_with);
    }
    else
    {
      cout << "Node pointers don't match the node to be replaced" << endl;
    }
  }
  else if (to_replace->parent->getType() == NodeType::UNARY_OPERATOR)
  {
    UnaOpNode* parent = static_cast<UnaOpNode*>(to_replace->parent);
    parent->node = std::move(replace_with);
  }
}
