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

bool BinMinus::interpret(const unordered_set<InterpretType> &flags)
{
  unique_ptr<Node> res_node;
  string left_str;
  string right_str;
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
    return true;
  }
  if (!(is_left_leaf && is_right_leaf))
  {
//    if (!(is_left_leaf || is_right_leaf))
//    {

//    }
//    else
//    {
      if (!is_left_leaf && !change)
      {
        if (node_left->tok.type == TokenType::LPAREN)
        {
          unique_ptr<Node> paren_items;
          UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_left.get());
          paren_items = std::move(una_op_node->node);
          NodeUtils::replaceNode(node_left.get(), paren_items);
          change = true;
        }
        else if (node_left->tok.type == TokenType::MINUS)
        {
          if (is_right_leaf)
          {
            left_str = node_left->to_repr();
            right_str = node_right->to_repr();

            double lhs = std::stod(left_str);
            double rhs = std::stod(right_str);
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
              res_node = std::make_unique<UnaMinus>(minus_tok, res_node);
            }

            NodeUtils::replaceNode(this, res_node);
            change = true;
          }
        }
      }
      if (!is_right_leaf && !change)
      {
        if (node_right->tok.type == TokenType::LPAREN)
        {
          unique_ptr<Node> paren_items;
          UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_right.get());
          paren_items = std::move(una_op_node->node);
          if (paren_items->tok.type == TokenType::MINUS)
          {
            unique_ptr<Node> rhs;
            unique_ptr<Node> lhs = std::move(node_left);
            una_op_node = static_cast<UnaOpNode*>(paren_items.get());
            rhs = std::move(una_op_node->node);
            Token plus_tok;
            plus_tok.type = TokenType::PLUS;
            unique_ptr<Node> result = std::make_unique<BinPlus>(lhs, plus_tok, rhs);
            NodeUtils::replaceNode(this, result);
            change = true;
          }
          if (!change)
          {
            una_op_node->node = std::move(paren_items);
          }
        }
      }
//    }
  }
  else
  {
    left_str = node_left->to_repr();
    right_str = node_right->to_repr();

    double lhs = std::stod(left_str);
    double rhs = std::stod(right_str);
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
      res_node = std::make_unique<UnaMinus>(minus_tok, res_node);
    }

    NodeUtils::replaceNode(this, res_node);
    change = true;
  }
  
  return change;
}
