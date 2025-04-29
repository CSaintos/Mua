#include "node_state/BinPlus.hpp"

using namespace std;
using namespace mua;

string BinPlus::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return "+";
  }
  return node_left->to_repr() + "+" + node_right->to_repr();
}

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

  unique_ptr<Node> lhs_node;
  unique_ptr<Node> rhs_node;
  unique_ptr<Node> left_numerator;
  unique_ptr<Node> left_denominator;
  unique_ptr<Node> right_numerator;
  unique_ptr<Node> right_denominator;
  bool removable_right_paren = false;
  bool is_lhs_paren = false;
  bool is_left_minus = false;
  bool is_right_minus = false;

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
  
  if (lhs_node != nullptr && rhs_node != nullptr)
  {
    if (lhs_node->isLeaf() && rhs_node->isLeaf())
    {
      if (is_left_minus)
      {
        lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
      }
      if (is_right_minus)
      {
        lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node, rhs_node);
        NodeUtils::replaceNode(node, lhs_node);
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

        lhs_node = node_factory->produceNode(res_tok);

        if (is_minus)
        {
          lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
        }

        NodeUtils::replaceNode(node, lhs_node);
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
            left_numerator = std::move(bin_op_node->node_left);
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
            right_numerator = std::move(bin_op_node->node_left);
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
    if (left_numerator->isLeaf() && left_denominator->isLeaf())
    {
      if (left_denominator->tok.type == TokenType::DIGIT && rhs_node->tok.type == TokenType::DIGIT)
      {
        int lhs_denominator = std::stod(left_denominator->to_repr());
        int rhs = std::stod(rhs_node->to_repr());
        int rhs_numerator = lhs_denominator * rhs;
        Token tok_value;
        tok_value.type = TokenType::DIGIT;
        tok_value.lexemes = std::to_string(rhs_numerator);
        right_numerator = node_factory->produceNode(tok_value);
        if (is_right_minus)
        {
          right_numerator = node_factory->produceNode(TokenType::MINUS, right_numerator);
        }
        tok_value.lexemes = std::to_string(lhs_denominator);
        right_denominator = node_factory->produceNode(tok_value);
        unique_ptr<Node> fraction = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
        fraction->meta_data.is_const_fraction = true;
        NodeUtils::replaceNode(node_right, fraction);

        if (is_left_minus)
        {
          left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
        }
        lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);
        NodeUtils::replaceNode(node_left, lhs_node);

        change = true;
      }
    }
  }
  else if (right_numerator != nullptr && right_denominator != nullptr && lhs_node != nullptr)
  {
    if (right_numerator->isLeaf() && right_denominator->isLeaf())
    {
      if (right_denominator->tok.type == TokenType::DIGIT && lhs_node->tok.type == TokenType::DIGIT)
      {
        int rhs_denominator = std::stod(right_denominator->to_repr());
        int lhs = std::stod(lhs_node->to_repr());
        int lhs_numerator = rhs_denominator * lhs;
        Token tok_value;
        tok_value.type = TokenType::DIGIT;
        tok_value.lexemes = std::to_string(lhs_numerator);
        left_numerator = node_factory->produceNode(tok_value);
        if (is_left_minus)
        {
          left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
        }
        tok_value.lexemes = std::to_string(rhs_denominator);
        left_denominator = node_factory->produceNode(tok_value);
        unique_ptr<Node> fraction = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);
        fraction->meta_data.is_const_fraction = true;
        NodeUtils::replaceNode(node_left, fraction);
        
        if (is_right_minus)
        {
          right_numerator = node_factory->produceNode(TokenType::MINUS, right_numerator);
        }
        rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
        NodeUtils::replaceNode(node_right, rhs_node);

        change = true;
      }
    }
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && right_numerator != nullptr && right_denominator != nullptr)
  {
    if (left_denominator->isLeaf() && right_denominator->isLeaf())
    {
      if (left_denominator->tok.type == TokenType::DIGIT && right_denominator->tok.type == TokenType::DIGIT)
      {
        int lhs_denominator = std::stod(left_denominator->to_repr());
        int rhs_denominator = std::stod(right_denominator->to_repr());

        if (lhs_denominator == rhs_denominator)
        {
          if (is_left_minus)
          {
            left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
          }

          unique_ptr<Node> numerator;
          if (!is_right_minus)
          {
            numerator = node_factory->produceNode(TokenType::PLUS, left_numerator, right_numerator);
          }
          else
          {
            numerator = node_factory->produceNode(TokenType::MINUS, left_numerator, right_numerator);
          }
          numerator = node_factory->produceNode(TokenType::LPAREN, numerator);
          unique_ptr<Node> fraction = node_factory->produceNode(TokenType::FSLASH, numerator, left_denominator);

          NodeUtils::replaceNode(node, fraction);
          change = true;
        }
        else
        {
          int gcd = std::gcd(lhs_denominator, rhs_denominator);
          int denominator = (lhs_denominator / gcd) * rhs_denominator; 
          int lhs_numerator = std::stod(left_numerator->to_repr());
          int rhs_numerator = std::stod(right_numerator->to_repr());
          lhs_numerator = lhs_numerator * (rhs_denominator / gcd);
          rhs_numerator = rhs_numerator * (lhs_denominator / gcd);

          left_numerator->tok.lexemes = std::to_string(lhs_numerator);
          right_numerator->tok.lexemes = std::to_string(rhs_numerator);
          left_denominator->tok.lexemes = std::to_string(denominator);
          right_denominator->tok.lexemes = std::to_string(denominator);

          if (is_left_minus)
          {
            left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
          }
          lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);
          rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
          lhs_node->meta_data.is_const_fraction = true;
          rhs_node->meta_data.is_const_fraction = true;
          if (!is_right_minus)
          {
            node->setNodes(lhs_node, rhs_node);
          }
          else
          {
            lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node, rhs_node);
            NodeUtils::replaceNode(node, lhs_node);
          }
          change = true;
        }
      }
    }
  }

  return change;
}

