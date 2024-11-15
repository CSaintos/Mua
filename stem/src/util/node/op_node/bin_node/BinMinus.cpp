#include "BinMinus.hpp"
#include "NumberUtils.hpp"
#include <cmath>

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
  bool left_change = false;
  bool right_change = false;
  bool change = false;
  bool is_left_leaf = true;
  bool is_right_leaf = true;

  if (!node_left->isLeaf())
  {
    bool proceed = true;
    if (node_left->tok.type == TokenType::FSLASH)
    {
      FSlash* fslash = static_cast<FSlash*>(node_left.get());
      if (fslash->is_const_fraction)
      {
        proceed = false;
      }
    }
    if (proceed)
    {
      left_change = node_left->interpret();
      change = left_change || change;
    }
    is_left_leaf = false;
  }
  if (!node_right->isLeaf())
  {
    bool proceed = true;
    if (node_right->tok.type == TokenType::FSLASH)
    {
      FSlash* fslash = static_cast<FSlash*>(node_right.get());
      if (fslash->is_const_fraction)
      {
        proceed = false;
      }
    }
    if (proceed)
    {
      right_change = node_right->interpret();
      change = right_change || change;
    }
    is_right_leaf = false;
  }
  if (change)
  {
    return true;
  }

  unique_ptr<Node> lhs_node;
  unique_ptr<Node> rhs_node;
  unique_ptr<Node> left_numerator;
  unique_ptr<Node> left_denominator;
  unique_ptr<Node> right_numerator;
  unique_ptr<Node> right_denominator;
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
    else if (node_left->tok.type == TokenType::FSLASH)
    {
      BinOpNode* bin_op_node = static_cast<BinOpNode*>(node_left.get());
      UnaOpNode* una_op_node;

      if (bin_op_node->node_left->tok.type == TokenType::MINUS)
      {
        is_left_minus = !is_left_minus;
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
        is_left_minus = !is_left_minus;
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
      if (una_op_node->node->tok.type == TokenType::FSLASH)
      {
        BinOpNode* bin_op_node = static_cast<BinOpNode*>(una_op_node->node.get());

        if (bin_op_node->node_left->tok.type == TokenType::MINUS)
        {
          is_left_minus = !is_left_minus;
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
          is_left_minus = !is_left_minus;
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
      is_right_minus = true;

      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        rhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
      }
    }
    else if (node_right->tok.type == TokenType::FSLASH)
    {
      BinOpNode* bin_op_node = static_cast<BinOpNode*>(node_right.get());
      UnaOpNode* una_op_node;
      
      if  (bin_op_node->node_left->tok.type == TokenType::MINUS)
      {
        is_right_minus = !is_right_minus;
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
        is_right_minus = !is_right_minus;
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
      if (una_op_node->node->tok.type == TokenType::FSLASH)
      {
        BinOpNode* bin_op_node = static_cast<BinOpNode*>(una_op_node->node.get());

        if (bin_op_node->node_left->tok.type == TokenType::MINUS)
        {
          is_right_minus = !is_right_minus;
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
          is_right_minus = !is_right_minus;
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
      if (is_left_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::MINUS;
        lhs_node = std::make_unique<UnaMinus>(tok_minus, lhs_node);
      }
      if (is_right_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::PLUS;
        lhs_node = std::make_unique<BinPlus>(lhs_node, tok_minus, rhs_node);
        NodeUtils::replaceNode(this, lhs_node);
        change = true;
      }
      else
      {
        int lhs = std::stod(lhs_node->to_repr());
        int rhs = std::stod(rhs_node->to_repr());
        int result = lhs - rhs;
        bool is_minus = false;

        if (result < 0)
        {
          result = result * -1;
          is_minus = true;
        }

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
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && rhs_node != nullptr)
  {
    if (left_numerator->isLeaf() && left_denominator->isLeaf())
    {
      if (left_denominator->tok.type == TokenType::DIGIT && rhs_node->tok.type == TokenType::DIGIT)
      {
        int lhs_denominator = std::stod(left_denominator->to_repr());
        int rhs = std::stod(rhs_node->to_repr());
        int rhs_denominator = lhs_denominator * rhs;
        Token tok_value;
        tok_value.type = TokenType::DIGIT;
        tok_value.lexemes = std::to_string(rhs_denominator);
        right_numerator = std::make_unique<ValueNode>(tok_value);
        if (is_right_minus)
        {
          Token tok_minus;
          tok_minus.type = TokenType::MINUS;
          right_numerator = std::make_unique<UnaMinus>(tok_minus, right_numerator);
        }
        tok_value.lexemes = std::to_string(lhs_denominator);
        right_denominator = std::make_unique<ValueNode>(tok_value);
        Token tok_fslash;
        tok_fslash.type = TokenType::FSLASH;
        unique_ptr<Node> fraction = std::make_unique<FSlash>(right_numerator, tok_fslash, right_denominator);
        FSlash* fslash = static_cast<FSlash*>(fraction.get());
        fslash->is_const_fraction = true;
        NodeUtils::replaceNode(node_right.get(), fraction);

        if (is_left_minus)
        {
          Token tok_minus;
          tok_minus.type = TokenType::MINUS;
          left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
        }
        lhs_node = std::make_unique<FSlash>(left_numerator, tok_fslash, left_denominator);
        NodeUtils::replaceNode(node_left.get(), lhs_node);

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
        int lhs_denominator = rhs_denominator * lhs;
        Token tok_value;
        tok_value.type = TokenType::DIGIT;
        tok_value.lexemes = std::to_string(lhs_denominator);
        left_numerator = std::make_unique<ValueNode>(tok_value);
        if (is_left_minus)
        {
          Token tok_minus;
          tok_minus.type = TokenType::MINUS;
          left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
        }
        tok_value.lexemes = std::to_string(rhs_denominator);
        left_denominator = std::make_unique<ValueNode>(tok_value);
        Token tok_fslash;
        tok_fslash.type = TokenType::FSLASH;
        unique_ptr<Node> fraction = std::make_unique<FSlash>(left_numerator, tok_fslash, left_denominator);
        FSlash* fslash = static_cast<FSlash*>(fraction.get());
        fslash->is_const_fraction = true;
        NodeUtils::replaceNode(node_left.get(), fraction);

        if (is_right_minus)
        {
          Token tok_minus;
          tok_minus.type = TokenType::MINUS;
          right_numerator = std::make_unique<UnaMinus>(tok_minus, right_numerator);
        }
        rhs_node = std::make_unique<FSlash>(right_numerator, tok_fslash, right_denominator);
        NodeUtils::replaceNode(node_right.get(), rhs_node);

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
            Token tok_minus;
            tok_minus.type = TokenType::MINUS;
            left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
          }

          unique_ptr<Node> numerator;
          if (!is_right_minus)
          {
            Token tok_minus;
            tok_minus.type = TokenType::MINUS;
            numerator = std::make_unique<BinMinus>(left_numerator, tok_minus, right_numerator);
          }
          else
          {
            Token tok_plus;
            tok_plus.type = TokenType::PLUS;
            numerator = std::make_unique<BinPlus>(left_numerator, tok_plus, right_numerator);
          }
          Token tok_paren;
          tok_paren.type = TokenType::LPAREN;
          numerator = std::make_unique<Paren>(tok_paren, numerator);
          Token tok_fslash;
          tok_fslash.type = TokenType::FSLASH;
          unique_ptr<Node> fraction = std::make_unique<FSlash>(numerator, tok_fslash, left_denominator);

          NodeUtils::replaceNode(this, fraction);
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
            Token tok_minus;
            tok_minus.type = TokenType::MINUS;
            left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
          }
          Token tok_fslash;
          tok_fslash.type = TokenType::FSLASH;
          lhs_node = std::make_unique<FSlash>(left_numerator, tok_fslash, left_denominator);
          rhs_node = std::make_unique<FSlash>(right_numerator, tok_fslash, right_denominator);
          FSlash* fslash;
          fslash = static_cast<FSlash*>(lhs_node.get());
          fslash->is_const_fraction = true;
          fslash = static_cast<FSlash*>(rhs_node.get());
          fslash->is_const_fraction = true;
          if (!is_right_minus)
          {
            node_left = std::move(lhs_node);
            node_left->parent = this;
            node_right = std::move(rhs_node);
            node_right->parent = this;
          }
          else
          {
            Token tok_minus;
            tok_minus.type = TokenType::MINUS;
            lhs_node = std::make_unique<BinMinus>(lhs_node, tok_minus, rhs_node);
            NodeUtils::replaceNode(this, lhs_node);
          }
          change = true;
        }
      }
    }
  }
  
  return change;
}

unique_ptr<Node> BinMinus::copy()
{
  unique_ptr<Node> lhs_node = node_left->copy();
  unique_ptr<Node> rhs_node = node_right->copy();
  return std::make_unique<BinMinus>(node_left, tok, node_right);
}
