#include "node_state/FSlash.hpp"

using namespace std;
using namespace mua;

string FSlash::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return "/";
  }
  return node_left->to_repr() + "/" + node_right->to_repr();
}

bool FSlash::interpret(const unordered_set<InterpretType> &flags)
{
  bool left_change = false;
  bool right_change = false;
  bool change = false;
  bool is_left_leaf = true;
  bool is_right_leaf = true;

  if (!node_left->isLeaf()) 
  {
    left_change = node_left->interpret(flags);
    change = left_change || change;
    is_left_leaf = false;
  }
  if (!node_right->isLeaf())
  {
    right_change = node_right->interpret(flags);
    change = right_change || change;
    is_right_leaf = false;
  }
  if (change || node->meta_data.is_const_fraction)
  {
    return change;
  }

  unique_ptr<Node> lhs_node;
  unique_ptr<Node> rhs_node;
  unique_ptr<Node> left_numerator;
  unique_ptr<Node> left_denominator;
  unique_ptr<Node> right_numerator;
  unique_ptr<Node> right_denominator;
  bool is_left_minus = false;
  bool is_right_minus = false;
  bool is_minus = false;
  bool removable_right_paren = false;
  bool is_lhs_paren = false;
  
  extractNodeChildrenData
  (
    lhs_node,
    rhs_node,
    left_numerator,
    left_denominator,
    right_numerator,
    right_denominator,
    is_left_minus,
    is_right_minus,
    removable_right_paren,
    is_lhs_paren,
    is_left_leaf,
    is_right_leaf
  );
      
  is_minus = is_left_minus != is_right_minus;
  
  if (lhs_node != nullptr && rhs_node != nullptr)
  {
    if (lhs_node->isLeaf() && rhs_node->isLeaf())
    {
      int lhs = std::stod(lhs_node->to_repr());
      int rhs = std::stod(rhs_node->to_repr());
      int gcd = std::gcd(lhs, rhs);

      if (gcd == 1)
      {
        if (flags.count(InterpretType::DECIMALIZE) > 0)
        {
          double result = double(lhs) / double(rhs);
          string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));
          Token res_tok;
          res_tok.type = TokenType::DIGIT;
          res_tok.lexemes = result_str;
          lhs_node = node_factory->produceNode(res_tok);
          if (is_minus)
          {
            lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
          }
          NodeUtils::replaceNode(node, lhs_node);
          change = true;
        }
        else if (rhs == 1)
        {
          if (is_minus)
          {
            lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
          }
          NodeUtils::replaceNode(node, lhs_node);
          change = true;
        }
        else if (removable_right_paren)
        {
          if (is_right_minus)
          {
            rhs_node = node_factory->produceNode(TokenType::MINUS, rhs_node);
          }
          NodeUtils::replaceNode(node_right, rhs_node);
          change = true;
        }
      }
      else
      {
        lhs = lhs / gcd;
        rhs = rhs / gcd;
        lhs_node->tok.lexemes = std::to_string(lhs);
        if (is_minus)
        {
          lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
        }
        if (rhs != 1)
        {
          rhs_node->tok.lexemes = std::to_string(rhs);
          NodeUtils::replaceNode(node_left, lhs_node);
          NodeUtils::replaceNode(node_right, rhs_node);
        }
        else
        {
          NodeUtils::replaceNode(node, lhs_node);
        }
        change = true;
      }
    }
    else
    {
      if (!lhs_node->isLeaf())
      {
        if (is_left_minus)
        {
          if (lhs_node->getType() == NodeType::BINARY_OPERATOR)
          {
            BinOpNode* bin_op_node = static_cast<BinOpNode*>(lhs_node.get());
            unique_ptr<Node> left_numerator = std::move(bin_op_node->node_left);
            left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
            bin_op_node->setLeftNode(left_numerator);
          }
        }
        NodeUtils::replaceNode(node_left, lhs_node);
      }
      if (!rhs_node->isLeaf())
      {
        if (is_right_minus)
        {
          if (rhs_node->getType() == NodeType::BINARY_OPERATOR)
          {
            BinOpNode* bin_op_node = static_cast<BinOpNode*>(rhs_node.get());
            unique_ptr<Node> right_numerator = std::move(bin_op_node->node_left);
            right_numerator = node_factory->produceNode(TokenType::MINUS, right_numerator);
            bin_op_node->setLeftNode(right_numerator);
          }
        }
        if (rhs_node->tok.type == TokenType::FSLASH)
        {
          rhs_node = node_factory->produceNode(TokenType::LPAREN, rhs_node);
        }
        NodeUtils::replaceNode(node_right, rhs_node);
      }
      change = true;
    }
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && rhs_node != nullptr)
  {
    unique_ptr<Node> denominator = node_factory->produceNode(TokenType::ASTERISK, left_denominator, rhs_node);
    unique_ptr<Node> paren = node_factory->produceNode(TokenType::LPAREN, denominator);
    if (is_minus)
    {
      left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
    }
    NodeUtils::replaceNode(node_left, left_numerator);
    NodeUtils::replaceNode(node_right, paren);
    change = true;
  }
  else if (right_numerator != nullptr && right_denominator != nullptr && lhs_node != nullptr)
  {
    unique_ptr<Node> numerator = node_factory->produceNode(TokenType::ASTERISK, lhs_node, right_denominator);
    if (is_minus)
    {
      numerator = node_factory->produceNode(TokenType::LPAREN, numerator);
      numerator = node_factory->produceNode(TokenType::MINUS, numerator);
    }

    NodeUtils::replaceNode(node_left, numerator);
    NodeUtils::replaceNode(node_right, right_numerator);
    change = true;
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && right_numerator != nullptr && right_denominator != nullptr)
  {
    unique_ptr<Node> numerator = node_factory->produceNode(TokenType::ASTERISK, left_numerator, right_denominator);
    numerator = node_factory->produceNode(TokenType::LPAREN, numerator);
    if (is_minus)
    {
      numerator = node_factory->produceNode(TokenType::MINUS, numerator);
    }
    unique_ptr<Node> denominator = node_factory->produceNode(TokenType::ASTERISK, left_denominator, right_numerator);
    denominator = node_factory->produceNode(TokenType::LPAREN, denominator);
    
    NodeUtils::replaceNode(node_left, numerator);
    NodeUtils::replaceNode(node_right, denominator);
    change = true;
  }

  return change;
}

