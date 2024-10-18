#include "FSlash.hpp"

using namespace std;
using namespace stem;

FSlash::FSlash(Token &tok_op)
  : BinOpNode(tok_op)
{}

FSlash::FSlash(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

FSlash::FSlash(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

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
  if (change)
  {
    return change;
  }
  if (!(is_left_leaf && is_right_leaf)) // not the case: both are leaves
  {
    if (!(is_left_leaf || is_right_leaf)) // not even the case: either one is a leaf
    {
      if (node_left->tok.type == TokenType::FSLASH && node_right->tok.type == TokenType::FSLASH)
      {
        cout << "Not implemented yet (1)" << endl;
      }
      else 
      {
        cout << "Not implemented yet (2)" << endl;  
      }
    }
    else 
    {
      if (!is_left_leaf)
      {
        if (node_left->tok.type == TokenType::FSLASH)
        {
          unique_ptr<Node> left_numerator;
          unique_ptr<Node> left_denominator;
          unique_ptr<Node> right_denominator;
          BinOpNode* bin_op_node = static_cast<BinOpNode*>(node_left.get());
          left_numerator = std::move(bin_op_node->node_left);
          node_left = std::move(left_numerator);
          node_left->parent = this;
          left_denominator = std::move(bin_op_node->node_right);
          right_denominator = std::move(node_right);
          Token tok_op;
          tok_op.type = TokenType::ASTERISK;
          unique_ptr<Node> denominator = std::make_unique<Asterisk>(left_denominator, tok_op, right_denominator);
          Token tok_paren;
          tok_paren.type = TokenType::LPAREN;
          unique_ptr<Node> paren = std::make_unique<Paren>(tok_paren, denominator);
          node_right = std::move(paren);
          node_right->parent = this;
          change = true;
        }
        else if (node_left->tok.type == TokenType::MINUS)
        {
          unique_ptr<Node> res_node;
          unique_ptr<Node> lhs_node;
          unique_ptr<Node> rhs_node;

          UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node_left.get());

          if (una_op_node->node->tok.type == TokenType::DIGIT && node_right->tok.type == TokenType::DIGIT)
          {
            lhs_node = NumberUtils::fractionalize(una_op_node->node->to_repr());
            rhs_node = NumberUtils::fractionalize(node_right->to_repr());

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
                  Token minus_tok;
                  minus_tok.type = TokenType::MINUS;
                  res_node = std::make_unique<ValueNode>(res_tok);
                  res_node = std::make_unique<UnaMinus>(minus_tok, res_node);
                  NodeUtils::replaceNode(this, res_node);
                  change = true;
                }
              }
              else
              {
                lhs = lhs / gcd;
                rhs = rhs / gcd;
                lhs_node->tok.lexemes = std::to_string(lhs);
                rhs_node->tok.lexemes = std::to_string(rhs);
                una_op_node->node = std::move(lhs_node);
                una_op_node->node->parent = una_op_node;
                node_right = std::move(rhs_node);
                node_right->parent = this;
                change = true;
              }
            }
          }
          else
          {
            cout << "Not implemented yet (5)" << endl;
          }
        }
        else
        {
          cout << "Not implemented yet (3)" << endl;
        }
      }
      else
      {
        cout << "Not implemented yet (4)" << endl;
      }
    }
  }
  else
  {
    unique_ptr<Node> res_node;
    unique_ptr<Node> lhs_node;
    unique_ptr<Node> rhs_node;

    if (node_left->tok.type == TokenType::DIGIT &&
    node_right->tok.type == TokenType::DIGIT)
    {
      lhs_node = NumberUtils::fractionalize(node_left->to_repr());
      rhs_node = NumberUtils::fractionalize(node_right->to_repr());

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
            res_node = std::make_unique<ValueNode>(res_tok);
            NodeUtils::replaceNode(this, res_node);
            change = true;
          }
        }
        else
        {
          lhs = lhs / gcd;
          rhs = rhs / gcd;
          lhs_node->tok.lexemes = std::to_string(lhs);
          rhs_node->tok.lexemes = std::to_string(rhs);
          node_left = std::move(lhs_node);
          node_left->parent = this;
          node_right = std::move(rhs_node);
          node_right->parent = this;
          change = true;
        }
      }
      else
      {
        if (!lhs_node->isLeaf())
        {
          node_left = std::move(lhs_node);
        }
        if (!rhs_node->isLeaf())
        {
          node_right = std::move(rhs_node);
        }
        change = true;
      }
    }
  }

  return change;
}
