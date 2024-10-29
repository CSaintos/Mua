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

bool Asterisk::interpret(const unordered_set<InterpretType> &flags)
{
  bool change = false;
  bool left_change = false;
  bool right_change = false;
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
  unique_ptr<Node> rhs_node;
  unique_ptr<Node> lhs_node;
  bool is_minus = false;
  bool removable_right_paren = false;

  if (!is_left_leaf)
  {
    if (node_left->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_left.get());
      is_minus = !is_minus;
      
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
        is_minus = !is_minus;
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
      is_minus = !is_minus;
      
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
        is_minus = !is_minus;
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
      }
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        if (tok.type == TokenType::ASTERISK)
        {
          removable_right_paren = true;
        }
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
    int lhs = std::stod(lhs_node->to_repr());
    int rhs = std::stod(rhs_node->to_repr());
    int result = lhs * rhs;

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
  else
  {
    cout << "Not implemented yet (4)" << endl;
  }

  return change;
}
