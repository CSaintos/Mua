#include "node_state/Asterisk.hpp"

using namespace std;
using namespace mua;

string Asterisk::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return "*";
  }
  return node_left->to_repr() + "*" + node_right->to_repr();
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

  unique_ptr<Node> rhs_node;
  unique_ptr<Node> lhs_node;
  unique_ptr<Node> left_numerator;
  unique_ptr<Node> left_denominator;
  unique_ptr<Node> right_numerator;
  unique_ptr<Node> right_denominator;
  bool is_minus = false;
  bool removable_right_paren = false;

  if (!is_left_leaf)
  {
    if (node_left->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_left);
      is_minus = !is_minus;
      
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        lhs_node = NumberUtils::fractionalize(node_factory, una_op_node->node->to_repr());
      }
    }
    else if (node_left->tok.type == TokenType::LPAREN)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_left);

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        is_minus = !is_minus;
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
      }
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        lhs_node = NumberUtils::fractionalize(node_factory, una_op_node->node->to_repr());
      }
      if (una_op_node->node->tok.type == TokenType::FSLASH)
      {
        BinOpNode* bin_op_node = static_cast<BinOpNode*>(una_op_node->node.get());

        if (bin_op_node->node_left->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
          left_numerator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_left->tok.type == TokenType::DIGIT)
        {
          left_numerator = std::move(bin_op_node->node_left);
        }
        else
        {
          cout << "Not implemented yet (3)" << endl;
        }
        if (bin_op_node->node_right->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
          left_denominator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_right->tok.type == TokenType::DIGIT)
        {
          left_denominator = std::move(bin_op_node->node_right);
        }
        else
        {
          cout << "Not implemented yet (3)" << endl;
        }
      }
    }
    else
    {
      cout << "Not implemented yet (2)" << endl;
    }
  }
  else
  {
    if (node_left->tok.type == TokenType::DIGIT)
    {
      lhs_node = NumberUtils::fractionalize(node_factory, node_left->to_repr());
    }
  }

  if (!is_right_leaf)
  {
    if (node_right->tok.type == TokenType::MINUS)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_right);
      is_minus = !is_minus;
      
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        rhs_node = NumberUtils::fractionalize(node_factory, una_op_node->node->to_repr());
      }
    }
    else if (node->node_right->tok.type == TokenType::LPAREN)
    {
      UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_right);

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        is_minus = !is_minus;
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
      }
      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        if (tok->type == TokenType::ASTERISK)
        {
          // What's this for?
          removable_right_paren = true;
        }
        rhs_node = NumberUtils::fractionalize(node_factory, una_op_node->node->to_repr());
      }
      if (una_op_node->node->tok.type == TokenType::FSLASH)
      {
        BinOpNode* bin_op_node = static_cast<BinOpNode*>(una_op_node->node.get());

        if (bin_op_node->node_left->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
          right_numerator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_left->tok.type == TokenType::DIGIT)
        {
          right_numerator = std::move(bin_op_node->node_left);
        }
        else
        {
          cout << "Not implemented yet (3)" << endl;
        }
        if (bin_op_node->node_right->tok.type == TokenType::MINUS)
        {
          is_minus = !is_minus;
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
          right_denominator = std::move(una_op_node->node);
        }
        else if (bin_op_node->node_right->tok.type == TokenType::DIGIT)
        {
          right_denominator = std::move(bin_op_node->node_right);
        }
        else 
        {
          cout << "Not implemented yet (3)" << endl;
        }
      }
    }
    else
    {
      cout << "Not implemented yet (2)" << endl;
    }
  }
  else
  {
    if (node_right->tok.type == TokenType::DIGIT)
    {
      rhs_node = NumberUtils::fractionalize(node_factory, node_right->to_repr());
    }
  }

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
      cout << "Not implemented Asterisk where !lhs_node->isLeaf() || !rhs_node->isLeaf()" << endl;
    }
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && rhs_node != nullptr)
  {
    unique_ptr<Node> numerator = node_factory->produceNode(TokenType::ASTERISK, left_numerator, rhs_node);
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
