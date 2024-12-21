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

  if (!node_right->isLeaf())
  {
    right_change = node_right->interpret(flags);
    change = right_change || change;
    is_right_leaf = false;
  }
  if (!node_left->isLeaf())
  {
    left_change = node_left->interpret(flags);
    change = left_change || change;
    is_left_leaf = false;
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
      if (is_right_minus)
      {
        Token tok_value;
        tok_value.type = TokenType::DIGIT;
        tok_value.lexemes = "1";
        left_numerator = std::make_unique<ValueNode>(tok_value);
        if (is_left_minus)
        {
          Token tok_minus;
          tok_minus.type = TokenType::MINUS;
          lhs_node = std::make_unique<UnaMinus>(tok_minus, lhs_node);
        }
        Token tok_fslash;
        tok_fslash.type = TokenType::FSLASH;
        lhs_node = std::make_unique<FSlash>(left_numerator, tok_fslash, lhs_node);
        Token tok_paren;
        tok_paren.type = TokenType::LPAREN;
        lhs_node = std::make_unique<Paren>(tok_paren, lhs_node);

        NodeUtils::replaceNode(node_left.get(), lhs_node);
        NodeUtils::replaceNode(node_right.get(), rhs_node);
        change = true;
      }
      else if (lhs_node->tok.type == TokenType::DIGIT &&
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
    if (is_right_minus)
    {
      if (is_left_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::MINUS;
        left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
      }
      Token tok_fslash;
      tok_fslash.type = TokenType::FSLASH;
      lhs_node = std::make_unique<FSlash>(left_denominator, tok_fslash, left_numerator);
      Token tok_paren;
      tok_paren.type = TokenType::LPAREN;
      lhs_node = std::make_unique<Paren>(tok_paren, lhs_node);

      NodeUtils::replaceNode(node_left.get(), lhs_node);
      NodeUtils::replaceNode(node_right.get(), rhs_node);
      change = true;
    }
    else
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
  }
  else if (lhs_node != nullptr && right_numerator != nullptr && right_denominator != nullptr)
  {
    if (is_right_minus)
    {
      Token tok_value;
      tok_value.lexemes = "1";
      tok_value.type = TokenType::DIGIT;
      left_numerator = std::make_unique<ValueNode>(tok_value);
      if (is_left_minus)
      {
        Token tok_minus;
        tok_minus.type = TokenType::MINUS;
        left_numerator = std::make_unique<UnaMinus>(tok_minus, left_numerator);
      }
      Token tok_fslash;
      tok_fslash.type = TokenType::FSLASH;
      lhs_node = std::make_unique<FSlash>(left_numerator, tok_fslash, lhs_node);
      Token tok_paren;
      tok_paren.type = TokenType::LPAREN;
      lhs_node = std::make_unique<Paren>(tok_paren, lhs_node);

      rhs_node = std::make_unique<FSlash>(right_numerator, tok_fslash, right_denominator);
      rhs_node = std::make_unique<Paren>(tok_paren, rhs_node);

      NodeUtils::replaceNode(node_left.get(), lhs_node);
      NodeUtils::replaceNode(node_right.get(), rhs_node);
      change = true;
    }
    else
    {
      if (lhs_node->tok.type == TokenType::DIGIT &&
      right_numerator->tok.type == TokenType::DIGIT)
      {
        int rhs = std::stod(right_numerator->tok.lexemes);
        if (rhs != 1)
        {
          int lhs = std::stod(lhs_node->tok.lexemes);
          if (is_left_minus)
          {
            lhs *= -1;
          }  
          int result = std::pow(lhs, rhs);
          bool is_minus = false;
          if (result < 0)
          {
            result *= -1;
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

          Token tok_value;
          tok_value.lexemes = "1";
          tok_value.type = TokenType::DIGIT;
          right_numerator = std::make_unique<ValueNode>(tok_value);
          
          Token tok_fslash;
          tok_fslash.type = TokenType::FSLASH;
          rhs_node = std::make_unique<FSlash>(right_numerator, tok_fslash, right_denominator);
          Token tok_paren;
          tok_paren.type = TokenType::LPAREN;
          rhs_node = std::make_unique<Paren>(tok_paren, rhs_node);

          NodeUtils::replaceNode(node_left.get(), lhs_node);
          NodeUtils::replaceNode(node_right.get(), rhs_node);
          change = true;
        }
        else
        {
          if (right_denominator->tok.type == TokenType::DIGIT)
          {
            int root = std::stod(right_denominator->tok.lexemes);
            int radicand = std::stod(lhs_node->tok.lexemes);
            cout << "Looking for primes" << endl;
            std::list<int> primes = NumberUtils::factorize(radicand);
            cout << "Primes were found" << endl;
            std::list<int> groups;
            std::map<int, int> sorted_primes;

            for (
            std::list<int>::iterator itr = primes.begin(); 
            itr != primes.end(); itr++)
            {
              if (sorted_primes.contains(*itr))
              {
                if (sorted_primes[*itr] == root - 1)
                {
                  groups.push_back(*itr);
                  sorted_primes[*itr] = 0;
                }
                else
                {
                  sorted_primes[*itr]++;
                }
              }
              else
              {
                sorted_primes[*itr] = 1;
              }
            }

            int simple_radicand = 1;
            for (const auto &[key, value] : sorted_primes)
            {
              if (value != 0)
              {
                simple_radicand *= key * value;
              }
            }
            int rooted_int = 1;
            for (int i : groups)
            {
              rooted_int *= i;
            }

            if (rooted_int != 1)
            {
              change = true;
              if (simple_radicand == 1)
              {
                // TODO: case in which the is_left_minus = true 
                // This case has two subcases, root is even or odd.
                Token tok_value;
                tok_value.type = TokenType::DIGIT;
                tok_value.lexemes = std::to_string(rooted_int);
                lhs_node = std::make_unique<ValueNode>(tok_value);

                NodeUtils::replaceNode(this, lhs_node);
              }
              else
              {
                Token tok_value;
                tok_value.type = TokenType::DIGIT;
                tok_value.lexemes = std::to_string(simple_radicand);
                lhs_node = std::make_unique<ValueNode>(tok_value);

                //NodeUtils::replaceNode(node_left.get(), lhs_node);
                
                if (!this->parent)
                {
                  //lhs_node = std::move(node_left);
                  Token tok_fslash;
                  tok_fslash.type = TokenType::FSLASH;
                  rhs_node = std::make_unique<FSlash>(right_numerator, tok_fslash, right_denominator);
                  Token tok_caret;
                  tok_caret.type = TokenType::CARET;
                  rhs_node = std::make_unique<Caret>(lhs_node, tok_caret, rhs_node);
                  tok_value.lexemes = std::to_string(rooted_int); 
                  unique_ptr<Node> rooted_node = std::make_unique<ValueNode>(tok_value);
                  Token tok_mult;
                  tok_mult.type = TokenType::ASTERISK;
                  lhs_node = std::make_unique<Asterisk>(rooted_node, tok_mult, rhs_node);

                  NodeUtils::replaceNode(this, lhs_node);
                }
                else
                {
                  Token tok_fslash;
                  tok_fslash.type = TokenType::FSLASH;
                  rhs_node = std::make_unique<FSlash>(right_numerator, tok_fslash, right_denominator);
                  Token tok_caret;
                  tok_caret.type = TokenType::CARET;
                  rhs_node = std::make_unique<Caret>(lhs_node, tok_caret, rhs_node);
                  tok_value.lexemes = std::to_string(rooted_int);
                  unique_ptr<Node> rooted_node = std::make_unique<ValueNode>(tok_value);

                  switch (this->parent->tok.type)
                  {
                  case TokenType::PLUS:
                  case TokenType::MINUS:
                  {
                    Token tok_mult;
                    tok_mult.type = TokenType::ASTERISK;
                    lhs_node = std::make_unique<Asterisk>(rooted_node, tok_mult, rhs_node);
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(this->parent);
                    //lhs_node = std::move(node_left);
                    if (bin_op_node->node_left.get() == this)
                    {
                      NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    }
                    else
                    {
                      NodeUtils::replaceNode(bin_op_node->node_right.get(), lhs_node);
                    }
                    break;
                  }
                  case TokenType::FSLASH:
                  {
                    Token tok_mult;
                    tok_mult.type = TokenType::ASTERISK;
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(this->parent);
                    lhs_node = std::make_unique<Asterisk>(rooted_node, tok_mult, rhs_node);
                    if (bin_op_node->node_left.get() == this)
                    {
                      NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    }
                    else
                    {
                      Token tok_paren;
                      tok_paren.type = TokenType::LPAREN;
                      lhs_node = std::make_unique<Paren>(tok_paren, lhs_node);
                      NodeUtils::replaceNode(bin_op_node->node_right.get(), lhs_node);
                    }
                    break;
                  }
                  case TokenType::ASTERISK:
                  {
                    Token tok_mult;
                    tok_mult.type = TokenType::ASTERISK;
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(this->parent);
                    if (bin_op_node->node_left.get() == this)
                    {
                      lhs_node = std::make_unique<Asterisk>(bin_op_node->node_right, tok_mult, rooted_node);
                    }
                    else
                    {
                      lhs_node = std::make_unique<Asterisk>(bin_op_node->node_left, tok_mult, rooted_node);
                    }
                    NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    NodeUtils::replaceNode(bin_op_node->node_right.get(), rhs_node);
                    break;
                  }
                  case TokenType::LPAREN:
                  {
                    Token tok_mult;
                    tok_mult.type = TokenType::ASTERISK;
                    lhs_node = std::make_unique<Asterisk>(rooted_node, tok_mult, rhs_node);
                    UnaOpNode* una_op_node = static_cast<UnaOpNode*>(this->parent);
                    NodeUtils::replaceNode(una_op_node->node.get(), lhs_node);
                    break;
                  }
                  case TokenType::CARET:
                  {
                    Token tok_mult;
                    tok_mult.type = TokenType::ASTERISK;
                    lhs_node = std::make_unique<Asterisk>(rooted_node, tok_mult, rhs_node);
                    Token tok_paren;
                    tok_paren.type = TokenType::LPAREN;
                    lhs_node = std::make_unique<Paren>(tok_paren, lhs_node);
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(this->parent);
                    if (bin_op_node->node_right.get() == this)
                    {
                      NodeUtils::replaceNode(bin_op_node->node_right.get(), lhs_node);
                    }
                    else
                    {
                      NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    }
                    break;
                  }
                  default:
                    cout << "Not implemented yet where Caret parent node is" << TokenUtils::m_TS_map[this->parent->tok.type] << endl;
                    break;
                  }
                }
              }
            }
            else
            {
              cout << "Not implemented yet where Caret::rooted_int == 1" << endl;
              // TODO: GTAB method for flag = DECIMAL
            }
          }
          else
          {
            cout << "Not implemented yet where Caret::right_denominator != DIGIT" << endl;
          }
        }
      }
      else 
      {
        cout << "Not implemented yet where Caret::lhs_node != DIGIT || Caret::right_numerator != DIGIT" << endl;
      }
    }
  }
  else if (left_numerator != nullptr && 
  left_denominator != nullptr &&
  right_numerator != nullptr &&
  right_denominator != nullptr)
  {
    cout << "Not implemented yet where Caret::(left_numerator, left_denominator, right_numerator, right_denominator)" << endl;
  }
  

  return change;
}

unique_ptr<Node> Caret::copy()
{
  unique_ptr<Node> lhs_node = node_left->copy();
  unique_ptr<Node> rhs_node = node_right->copy();
  return std::make_unique<Caret>(lhs_node, tok, rhs_node);
}
