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
          // What's this for?
          removable_right_paren = true;
        }
        rhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
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
      rhs_node = NumberUtils::fractionalize(node_right->to_repr());
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

      lhs_node = std::make_unique<ValueNode>(res_tok);

      if (is_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::MINUS;
        lhs_node = std::make_unique<UnaMinus>(tok_minus, lhs_node);
      }

      NodeUtils::replaceNode(this, lhs_node);
      change = true;
    }
    else
    {
      cout << "Not implemented Asterisk where !lhs_node->isLeaf() || !rhs_node->isLeaf()" << endl;
    }
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && rhs_node != nullptr)
  {
    Token tok_mult;
    tok_mult.type = TokenType::ASTERISK;
    unique_ptr<Node> numerator = std::make_unique<Asterisk>(left_numerator, tok_mult, rhs_node);
    if (is_minus)
    {
      Token tok_paren;
      tok_paren.type = TokenType::LPAREN;
      numerator = std::make_unique<Paren>(tok_paren, numerator);
      Token tok_minus;
      tok_minus.type = TokenType::MINUS;
      numerator = std::make_unique<UnaMinus>(tok_minus, numerator);
    }
    Token tok_fslash;
    tok_fslash.type = TokenType::FSLASH;
    unique_ptr<Node> fraction = std::make_unique<FSlash>(numerator, tok_fslash, left_denominator);

    NodeUtils::replaceNode(this, fraction);
    change = true;
  }
  else if (right_numerator != nullptr && right_denominator != nullptr && lhs_node != nullptr)
  {
    Token tok_mult;
    tok_mult.type = TokenType::ASTERISK;
    unique_ptr<Node> numerator = std::make_unique<Asterisk>(lhs_node, tok_mult, right_numerator);
    if (is_minus)
    {
      Token tok_paren;
      tok_paren.type = TokenType::LPAREN;
      numerator = std::make_unique<Paren>(tok_paren, numerator);
      Token tok_minus;
      tok_minus.type = TokenType::MINUS;
      numerator = std::make_unique<UnaMinus>(tok_minus, numerator);
    }
    Token tok_fslash;
    tok_fslash.type = TokenType::FSLASH;
    unique_ptr<Node> fraction = std::make_unique<FSlash>(numerator, tok_fslash, right_denominator);

    NodeUtils::replaceNode(this, fraction);
    change = true;
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && right_numerator != nullptr && right_denominator != nullptr)
  {
    Token tok_mult;
    tok_mult.type = TokenType::ASTERISK;
    Token tok_paren;
    tok_paren.type = TokenType::LPAREN;
    if (is_minus)
    {
      Token tok_minus;
      tok_minus.type = TokenType::MINUS;
      left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
    }
    unique_ptr<Node> numerator = std::make_unique<Asterisk>(left_numerator, tok_mult, right_numerator);
    unique_ptr<Node> denominator = std::make_unique<Asterisk>(left_denominator, tok_mult, right_denominator);
    denominator = std::make_unique<Paren>(tok_paren, denominator);

    Token tok_fslash;
    tok_fslash.type = TokenType::FSLASH;
    unique_ptr<Node> fraction = std::make_unique<FSlash>(numerator, tok_fslash, denominator);
    NodeUtils::replaceNode(this, fraction);
    change = true;
  }

  return change;
}

unique_ptr<Node> Asterisk::copy()
{
  unique_ptr<Node> lhs_node = node_left->copy();
  unique_ptr<Node> rhs_node = node_right->copy();
  return std::make_unique<Asterisk>(lhs_node, tok, rhs_node);
}
