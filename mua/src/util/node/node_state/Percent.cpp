#include "node_state/Percent.hpp"
#include "op_node/BinOpNode.hpp"

using namespace std;
using namespace mua;

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
      int lhs = std::stod(lhs_node->tok.lexemes);
      int rhs = std::stod(rhs_node->tok.lexemes);
      int result = lhs % rhs;

      string result_str = std::to_string(result);

      Token res_tok;
      res_tok.lexemes = result_str;
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
    int l_numerator = std::stod(left_numerator->tok.lexemes);
    int l_denominator = std::stod(left_denominator->tok.lexemes);
    int rhs = std::stod(rhs_node->tok.lexemes);
    int truncate = l_numerator / (l_denominator * rhs) * rhs; 
    
    string truncate_str = std::to_string(truncate);

    Token truncate_tok;
    truncate_tok.lexemes = truncate_str;
    truncate_tok.type = TokenType::DIGIT;

    rhs_node = node_factory->produceNode(truncate_tok);
    lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);
    lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node, rhs_node);
    // 1st itr: makes equal factions, 2nd itr: subtracts numerators, 3rd itr: simplifies resulting fraction
    while (lhs_node->interpret());

    if (is_minus)
    {
      lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
    }

    NodeUtils::replaceNode(node, lhs_node);
    change = true;
  }
  else if (right_numerator != nullptr && right_denominator != nullptr && lhs_node != nullptr)
  {
    int lhs = std::stod(lhs_node->tok.lexemes);
    int r_numerator = std::stod(right_numerator->tok.lexemes);
    int r_denominator = std::stod(right_denominator->tok.lexemes);
    int truncate = (lhs * r_denominator / r_numerator) * r_numerator;

    string truncate_str = std::to_string(truncate);

    Token truncate_tok;
    truncate_tok.lexemes = truncate_str;
    truncate_tok.type = TokenType::DIGIT;

    right_numerator = node_factory->produceNode(truncate_tok);
    rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
    lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node, rhs_node);
    while(lhs_node->interpret());

    if (is_minus)
    {
      lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
    }

    NodeUtils::replaceNode(node, lhs_node);
    change = true;
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && right_numerator != nullptr && right_denominator != nullptr)
  {
    int l_numerator = std::stod(left_numerator->tok.lexemes);
    int l_denominator = std::stod(left_denominator->tok.lexemes);
    int r_numerator = std::stod(right_numerator->tok.lexemes);
    int r_denominator = std::stod(right_denominator->tok.lexemes);
    int truncate = (l_numerator * r_denominator ) / (l_denominator * r_numerator) * r_numerator;

    string truncate_str = std::to_string(truncate);
    
    Token truncate_tok;
    truncate_tok.lexemes = truncate_str;
    truncate_tok.type = TokenType::DIGIT;

    right_numerator = node_factory->produceNode(truncate_tok);
    rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
    lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);
    lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node, rhs_node);
    while(lhs_node->interpret());

    if (is_minus)
    {
      lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
    }

    NodeUtils::replaceNode(node, lhs_node);
    change = true;
  }

  return change;
}

