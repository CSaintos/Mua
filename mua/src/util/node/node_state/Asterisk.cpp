#include "node_state/Asterisk.hpp"

using namespace std;
using namespace mua;

string Asterisk::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    if (tok->type == TokenType::ASTERISK)
      return "*";
    return ""; // ADJACENT case
  }
  if (tok->type == TokenType::ASTERISK)
    return node_left->to_repr() + "*" + node_right->to_repr();
  return node_left->to_repr() + node_right->to_repr(); // ADJACENT case
}

bool Asterisk::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  bool left_change = false;
  bool right_change = false;
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
  if (change)
  {
    return change;
  }

  unique_ptr<Node> rhs_node;
  unique_ptr<Node> lhs_node;
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

  is_minus = (
    (is_left_minus ||
    is_right_minus) &&
    !(is_left_minus &&
    is_right_minus)
  );

  if (lhs_node != nullptr && rhs_node != nullptr)
  {
    if (lhs_node->isLeaf() && rhs_node->isLeaf())
    {
      int lhs = std::stod(lhs_node->to_repr());
      int rhs = std::stod(rhs_node->to_repr());
      int result = lhs * rhs;

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
        if (flags.count(InterpretType::DECIMALIZE) > 0)
        {
          lhs_node->meta_data.is_const_fraction = true;
        }

        node->setLeftNode(lhs_node);
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
        if (flags.count(InterpretType::DECIMALIZE) > 0)
        {
          rhs_node->meta_data.is_const_fraction = true;
        }
        
        node->setRightNode(rhs_node);
      }
      change = true;
    }
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && rhs_node != nullptr)
  {
    unique_ptr<Node> numerator = node_factory->produceNode(TokenType::ASTERISK, left_numerator, rhs_node);
    unique_ptr<Node> phony_parent = node_factory->produceNode(TokenType::SEMICOLON, numerator);
    phony_parent->interpret();
    numerator = std::move((static_cast<UnaOpNode*>(phony_parent.get()))->node);
    if (is_minus)
    {
      numerator = node_factory->produceNode(TokenType::LPAREN, numerator);
      numerator = node_factory->produceNode(TokenType::MINUS, numerator);
    }
    unique_ptr<Node> fraction = node_factory->produceNode(TokenType::FSLASH, numerator, left_denominator);

    NodeUtils::replaceNode(node, fraction);
    change = true;
  }
  else if (right_numerator != nullptr && right_denominator != nullptr && lhs_node != nullptr)
  {
    unique_ptr<Node> numerator = node_factory->produceNode(TokenType::ASTERISK, lhs_node, right_numerator);
    unique_ptr<Node> phony_parent = node_factory->produceNode(TokenType::SEMICOLON, numerator);
    phony_parent->interpret();
    numerator = std::move((static_cast<UnaOpNode*>(phony_parent.get()))->node);
    if (is_minus)
    {
      numerator = node_factory->produceNode(TokenType::LPAREN, numerator);
      numerator = node_factory->produceNode(TokenType::MINUS, numerator);
    }
    unique_ptr<Node> fraction = node_factory->produceNode(TokenType::FSLASH, numerator, right_denominator);

    NodeUtils::replaceNode(node, fraction);
    change = true;
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && right_numerator != nullptr && right_denominator != nullptr)
  {
    if (is_minus)
    {
      left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
    }
    unique_ptr<Node> numerator = node_factory->produceNode(TokenType::ASTERISK, left_numerator, right_numerator);
    unique_ptr<Node> denominator = node_factory->produceNode(TokenType::ASTERISK, left_denominator, right_denominator);
    denominator = node_factory->produceNode(TokenType::LPAREN, denominator);

    unique_ptr<Node> fraction = node_factory->produceNode(TokenType::FSLASH, numerator, denominator);
    NodeUtils::replaceNode(node, fraction);
    change = true;
  }

  return change;
}
