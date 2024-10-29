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

bool BinPlus::interpret(const unordered_set<InterpretType> &flags)
{
  bool left_change = false;
  bool right_change = false;
  bool change = false;
  bool is_left_leaf = true;
  bool is_right_leaf = true;

  if (!node_left->isLeaf())
  {
    left_change = node_left->interpret();
    change = left_change || change;
    is_left_leaf = false;
  }
  if (!node_right->isLeaf())
  {
    right_change = node_right->interpret();
    change = right_change || change;
    is_right_leaf = false;
  }
  if (change)
  {
    return change;
  }

  unique_ptr<Node> res_node;
  unique_ptr<Node> lhs_node;
  unique_ptr<Node> rhs_node;
  string left_str;
  string right_str;
  bool is_left_minus = false;
  bool is_right_minus = false;

  if (!is_left_leaf)
  {
    if (node_left->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_left.get());
      is_left_minus = true;

      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        lhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
      }
    }
    else if (node_left->tok.type == TokenType::LPAREN)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_left.get());

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        is_left_minus = true;
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
      }
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        lhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
      }
    }
  }
  else
  {
    if (node_left->tok.type == TokenType::DIGIT)
    {
      lhs_node = NumberUtils::fractionalize(node_left->to_repr());
    }
  }
  if (!is_right_leaf)
  {
    if (node_right->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_right.get());
      is_right_minus = true;

      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        rhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
      }
    }
    else if (node_right->tok.type == TokenType::LPAREN)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_right.get());

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        is_right_minus = true;
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
      }
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        rhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
      }
    }
  }
  else
  {
    if (node_right->tok.type == TokenType::DIGIT)
    {
      rhs_node = NumberUtils::fractionalize(node_right->to_repr());
    }
  }
  
  if (lhs_node->isLeaf() && rhs_node->isLeaf())
  {
    if (is_left_minus)
    {
      Token tok_minus;
      tok_minus.type = TokenType::MINUS;
      lhs_node = std::make_unique<UnaMinus>(tok_minus, lhs_node);
    }
    if (is_right_minus)
    {
      Token tok_minus;
      tok_minus.type = TokenType::MINUS;
      res_node = std::make_unique<BinMinus>(lhs_node, tok_minus, rhs_node);
      NodeUtils::replaceNode(this, res_node);
      change = true;
    }
    else
    {
      int lhs = std::stod(lhs_node->to_repr());
      int rhs = std::stod(rhs_node->to_repr());
      int result = lhs + rhs;
      bool is_minus = false;

      if (result < 0)
      {
        result = result * -1;
        is_minus = true;
      }

      Token res_tok;
      res_tok.lexemes = std::to_string(result);
      res_tok.type = TokenType::DIGIT;

      res_node = std::make_unique<ValueNode>(res_tok);

      if (is_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::MINUS;
        res_node = std::make_unique<UnaMinus>(tok_minus, res_node);
      }

      NodeUtils::replaceNode(this, res_node);
      change = true;
    }
  }
  else
  {
    if (!lhs_node->isLeaf())
    {
      if (is_left_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::MINUS;
        if (lhs_node->getType() == NodeType::BINARY_OPERATOR)
        {
          BinOpNode* bin_op_node = static_cast<BinOpNode*>(lhs_node.get());
          unique_ptr<Node> left_numerator = std::move(bin_op_node->node_left);
          left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
          bin_op_node->node_left = std::move(left_numerator);
          bin_op_node->node_left->parent = bin_op_node;
        }
      }
      NodeUtils::replaceNode(node_left.get(), lhs_node);
    }
    if (!rhs_node->isLeaf())
    {
      if (is_right_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::MINUS;
        if (rhs_node->getType() == NodeType::BINARY_OPERATOR)
        {
          BinOpNode* bin_op_node = static_cast<BinOpNode*>(rhs_node.get());
          unique_ptr<Node> right_numerator = std::move(bin_op_node->node_left);
          right_numerator = std::make_unique<UnaMinus>(tok_minus, right_numerator);
          bin_op_node->node_left = std::move(right_numerator);
          bin_op_node->node_left->parent = bin_op_node;
        }
      }
      if (rhs_node->tok.type == TokenType::FSLASH)
      {
        Token tok_paren;
        tok_paren.type = TokenType::LPAREN;
        rhs_node = std::make_unique<Paren>(tok_paren, rhs_node);
      }
      NodeUtils::replaceNode(node_right.get(), rhs_node);
    }
    change = true;
  }

  return change;
}
