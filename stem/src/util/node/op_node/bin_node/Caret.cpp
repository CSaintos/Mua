#include "Caret.hpp"

using namespace std;
using namespace stem;

Caret::Caret(Token &tok_op)
  : BinOpNode(tok_op)
{}

Caret::Caret(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

Caret::Caret(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

bool Caret::interpret(const unordered_set<InterpretType> &flags)
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
  bool is_lhs_paren = false;

  if (!is_left_leaf)
  {
    if (node_left->tok.type == TokenType::MINUS)
    {
      cout << "Not implemented yet where Caret node_left.tok.type == MINUS" << endl;
    }
    else if (node_left->tok.type == TokenType::FSLASH)
    {
      BinOpNode* bin_op_node = static_cast<BinOpNode*>(node_left.get());
      UnaOpNode* una_op_node;

      if (bin_op_node->node_left->tok.type == TokenType::MINUS)
      {
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
      is_lhs_paren = true;

      if (una_op_node->node->tok.type == TokenType::MINUS)
      {
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
        is_left_minus = !is_left_minus;
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
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
          left_numerator = std::move(una_op_node->node);
          is_left_minus = !is_left_minus;
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
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
          left_denominator = std::move(una_op_node->node);
          is_left_minus = !is_left_minus;
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
      is_right_minus = !is_right_minus;

      if (una_op_node->node->tok.type == TokenType::DIGIT)
      {
        rhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
      }
    }
    else if (node_right->tok.type == TokenType::FSLASH)
    {
      BinOpNode* bin_op_node = static_cast<BinOpNode*>(node_right.get());
      UnaOpNode* una_op_node;

      if (bin_op_node->node_left->tok.type == TokenType::MINUS)
      {
        una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
        right_numerator = std::move(una_op_node->node);
        is_right_minus = !is_right_minus;
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
        una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
        right_denominator = std::move(una_op_node->node);
        is_right_minus = !is_right_minus;
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
        una_op_node = static_cast<UnaOpNode*>(una_op_node->node.get());
        is_right_minus = !is_right_minus;
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
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_left.get());
          right_numerator = std::move(una_op_node->node);
          is_right_minus = !is_right_minus;
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
          una_op_node = static_cast<UnaOpNode*>(bin_op_node->node_right.get());
          right_denominator = std::move(una_op_node->node);
          is_right_minus = !is_right_minus;
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
      if (lhs_node->tok.type == TokenType::DIGIT &&
      rhs_node->tok.type == TokenType::DIGIT)
      {
        int lhs = std::stod(lhs_node->tok.lexemes);
        if (is_left_minus)
        {
          lhs = lhs * -1;
        }
        int rhs = std::stod(rhs_node->tok.lexemes);
        int result = std::pow(lhs, rhs);
        bool is_minus = false;
        
        if (result < 0)
        {
          result = result * -1;
          is_minus = true;
        }

        string result_str = NumberUtils::stripTrailingZeros(std::to_string(result));

        Token res_tok;
        res_tok.lexemes = result_str;
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
        if (lhs_node->tok.type == TokenType::FSLASH)
        {
          Token tok_paren;
          tok_paren.type = TokenType::LPAREN;
          lhs_node = std::make_unique<Paren>(tok_paren, lhs_node);
        }
        NodeUtils::replaceNode(node_left.get(), lhs_node);
      }
      if (!rhs_node->isLeaf())
      {
        NodeUtils::replaceNode(node_right.get(), rhs_node);
      }
      change = true;
    }
  }
  else if (left_numerator != nullptr && left_denominator != nullptr && rhs_node != nullptr)
  {
    unique_ptr<Node> rhs_node_copy = rhs_node->copy();
    if (is_left_minus)
    {
      Token tok_minus;
      tok_minus.type = TokenType::MINUS;
      left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
      Token tok_paren;
      tok_paren.type = TokenType::LPAREN;
      left_numerator = std::make_unique<Paren>(tok_paren, left_numerator);
    }
    Token tok_caret;
    tok_caret.type = TokenType::CARET;
    left_numerator = std::make_unique<Caret>(left_numerator, tok_caret, rhs_node_copy);
    left_denominator = std::make_unique<Caret>(left_denominator, tok_caret, rhs_node);
    Token tok_fslash;
    tok_fslash.type = TokenType::FSLASH;
    lhs_node = std::make_unique<FSlash>(left_numerator, tok_fslash, left_denominator);
    if (is_lhs_paren)
    {
      Token tok_paren;
      tok_paren.type = TokenType::LPAREN;
      lhs_node = std::make_unique<Paren>(tok_paren, lhs_node);
    }
    NodeUtils::replaceNode(this, lhs_node);
    change = true;
  }
  

  return change;
}

unique_ptr<Node> Caret::copy()
{
  unique_ptr<Node> lhs_node = node_left->copy();
  unique_ptr<Node> rhs_node = node_right->copy();
  return std::make_unique<Caret>(lhs_node, tok, rhs_node);
}
