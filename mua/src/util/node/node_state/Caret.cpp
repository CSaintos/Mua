#include "node_state/Caret.hpp"

using namespace std;
using namespace mua;

string Caret::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return "^";
  }
  return node_left->to_repr() + "^" + node_right->to_repr();
}

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

  unique_ptr<Node> lhs_node;
  unique_ptr<Node> rhs_node;
  unique_ptr<Node> left_numerator;
  unique_ptr<Node> left_denominator;
  unique_ptr<Node> right_numerator;
  unique_ptr<Node> right_denominator;
  bool is_left_minus = false;
  bool is_right_minus = false;
  bool is_lhs_paren = false;
  bool removable_right_paren;

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

  if (lhs_node != nullptr && rhs_node != nullptr)
  {
    if (lhs_node->isLeaf() && rhs_node->isLeaf())
    {
      if (is_right_minus)
      {
        Token tok_value;
        tok_value.type = TokenType::DIGIT;
        tok_value.lexemes = "1";
        left_numerator = node_factory->produceNode(tok_value);
        if (is_left_minus)
        {
          lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
        }
        lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, lhs_node);
        lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);

        node->setNodes(lhs_node, rhs_node);
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

        lhs_node = node_factory->produceNode(res_tok);

        if (is_minus)
        {
          lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
        }

        NodeUtils::replaceNode(node, lhs_node);
        change = true;
      }
    }
    else
    {
      if (!lhs_node->isLeaf())
      {
        if (lhs_node->tok.type == TokenType::FSLASH)
        {
          lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);
        }
        node->setLeftNode(lhs_node);
      }
      if (!rhs_node->isLeaf())
      {
        if (rhs_node->tok.type == TokenType::FSLASH)
        {
          rhs_node = node_factory->produceNode(TokenType::LPAREN, rhs_node);
        }
        node->setRightNode(rhs_node);
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
        left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
      }
      lhs_node = node_factory->produceNode(TokenType::FSLASH, left_denominator, left_numerator);
      lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);

      node->setNodes(lhs_node, rhs_node);
      change = true;
    }
    else
    {
      unique_ptr<Node> rhs_node_copy = rhs_node->copy();
      if (is_left_minus)
      {
        left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
        left_numerator = node_factory->produceNode(TokenType::LPAREN, left_numerator);
      }
      left_numerator = node_factory->produceNode(TokenType::CARET, left_numerator, rhs_node_copy);
      left_denominator = node_factory->produceNode(TokenType::CARET, left_denominator, rhs_node);
      lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);
      if (is_lhs_paren)
      {
        lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);
      }
      NodeUtils::replaceNode(node, lhs_node);
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
      left_numerator = node_factory->produceNode(tok_value);
      if (is_left_minus)
      {
        left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
      }
      lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, lhs_node);
      lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);

      rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
      rhs_node = node_factory->produceNode(TokenType::LPAREN, rhs_node);

      node->setNodes(lhs_node, rhs_node);
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

          lhs_node = node_factory->produceNode(res_tok);
          if (is_minus)
          {
            lhs_node = node_factory->produceNode(TokenType::MINUS, lhs_node);
          }

          Token tok_value;
          tok_value.lexemes = "1";
          tok_value.type = TokenType::DIGIT;
          right_numerator = node_factory->produceNode(tok_value);
          
          rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
          rhs_node = node_factory->produceNode(TokenType::LPAREN, rhs_node);

          node->setNodes(lhs_node, rhs_node);
          change = true;
        }
        else
        {
          if (right_denominator->tok.type == TokenType::DIGIT)
          {
            int root = std::stod(right_denominator->tok.lexemes);
            int radicand = std::stod(lhs_node->tok.lexemes);
            if (radicand == 1)
            {
              NodeUtils::replaceNode(node, lhs_node);
              return true;
            }

            //cout << "Looking for primes" << endl;
            std::list<int> primes = NumberUtils::factorize(radicand);
            //cout << "Primes were found" << endl;
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
                lhs_node = node_factory->produceNode(tok_value);

                NodeUtils::replaceNode(node, lhs_node);
              }
              else
              {
                Token tok_value;
                tok_value.type = TokenType::DIGIT;
                tok_value.lexemes = std::to_string(simple_radicand);
                lhs_node = node_factory->produceNode(tok_value);
                
                // This case may never happen since there will always be a parent of SEMICOLON
                if (!node->parent)
                {
                  rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
                  rhs_node = node_factory->produceNode(TokenType::CARET, lhs_node, rhs_node);
                  tok_value.lexemes = std::to_string(rooted_int); 
                  lhs_node = node_factory->produceNode(tok_value);
                  lhs_node = node_factory->produceNode(TokenType::ASTERISK, lhs_node, rhs_node);

                  NodeUtils::replaceNode(node, lhs_node);
                }
                else
                {
                  rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
                  rhs_node = node_factory->produceNode(TokenType::CARET, lhs_node, rhs_node);
                  tok_value.lexemes = std::to_string(rooted_int);
                  lhs_node = node_factory->produceNode(tok_value);

                  switch (node->parent->tok.type)
                  {
                  case TokenType::PLUS:
                  case TokenType::MINUS:
                  {
                    lhs_node = node_factory->produceNode(TokenType::ASTERISK, lhs_node, rhs_node);
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(node->parent);
                    if (bin_op_node->node_left.get() == node)
                    {
                      bin_op_node->setLeftNode(lhs_node);
                      //NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    }
                    else
                    {
                      bin_op_node->setRightNode(lhs_node);
                      //NodeUtils::replaceNode(bin_op_node->node_right.get(), lhs_node);
                    }
                    break;
                  }
                  case TokenType::FSLASH:
                  {
                    lhs_node = node_factory->produceNode(TokenType::ASTERISK, lhs_node, rhs_node);
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(node->parent);
                    if (bin_op_node->node_left.get() == node)
                    {
                      bin_op_node->setLeftNode(lhs_node);
                      //NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    }
                    else
                    {
                      lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);
                      bin_op_node->setRightNode(lhs_node);
                      //NodeUtils::replaceNode(bin_op_node->node_right.get(), lhs_node);
                    }
                    break;
                  }
                  case TokenType::ASTERISK:
                  {
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(node->parent);
                    if (bin_op_node->node_left.get() == node)
                    {
                      lhs_node = node_factory->produceNode(TokenType::ASTERISK, bin_op_node->node_right, lhs_node);
                    }
                    else
                    {
                      lhs_node = node_factory->produceNode(TokenType::ASTERISK, bin_op_node->node_left, lhs_node);
                    }
                    bin_op_node->setNodes(lhs_node, rhs_node);
                    //NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    //NodeUtils::replaceNode(bin_op_node->node_right.get(), rhs_node);
                    break;
                  }
                  case TokenType::LPAREN:
                  {
                    lhs_node = node_factory->produceNode(TokenType::ASTERISK, lhs_node, rhs_node);
                    UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node->parent);
                    una_op_node->setNode(lhs_node);
                    //NodeUtils::replaceNode(una_op_node->node.get(), lhs_node);
                    break;
                  }
                  case TokenType::SEMICOLON:
                  {
                    lhs_node = node_factory->produceNode(TokenType::ASTERISK, lhs_node, rhs_node);
                    UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node->parent);
                    una_op_node->setNode(lhs_node);
                    break;
                  }
                  case TokenType::CARET:
                  {
                    lhs_node = node_factory->produceNode(TokenType::ASTERISK, lhs_node, rhs_node);
                    lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);
                    BinOpNode* bin_op_node = static_cast<BinOpNode*>(node->parent);
                    if (bin_op_node->node_right.get() == node)
                    {
                      bin_op_node->setRightNode(lhs_node);
                      //NodeUtils::replaceNode(bin_op_node->node_right.get(), lhs_node);
                    }
                    else
                    {
                      bin_op_node->setLeftNode(lhs_node);
                      //NodeUtils::replaceNode(bin_op_node->node_left.get(), lhs_node);
                    }
                    break;
                  }
                  default:
                    cout << "Not implemented yet where Caret parent node is " << TokenUtils::m_TS_map[node->parent->tok.type] << endl;
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
    if (is_right_minus)
    {
      if (is_left_minus)
      {
        left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
      }
      lhs_node = node_factory->produceNode(TokenType::FSLASH, left_denominator, left_numerator);
      if (is_lhs_paren)
      {
        lhs_node = node_factory->produceNode(TokenType::LPAREN, lhs_node);
      }
      rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
      rhs_node = node_factory->produceNode(TokenType::LPAREN, rhs_node);

      node->setNodes(lhs_node, rhs_node);
      change = true;
    }
    else
    {
      unique_ptr<Node> right_numerator_copy = right_numerator->copy();
      unique_ptr<Node> right_denominator_copy = right_denominator->copy();

      if (is_left_minus)
      {
        left_numerator = node_factory->produceNode(TokenType::MINUS, left_numerator);
        left_numerator = node_factory->produceNode(TokenType::LPAREN, left_numerator);
      }
      rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator, right_denominator);
      rhs_node = node_factory->produceNode(TokenType::LPAREN, rhs_node);
      left_numerator = node_factory->produceNode(TokenType::CARET, left_numerator, rhs_node);
      rhs_node = node_factory->produceNode(TokenType::FSLASH, right_numerator_copy, right_denominator_copy);
      rhs_node = node_factory->produceNode(TokenType::LPAREN, rhs_node);
      left_denominator = node_factory->produceNode(TokenType::CARET, left_denominator, rhs_node);
      lhs_node = node_factory->produceNode(TokenType::FSLASH, left_numerator, left_denominator);

      NodeUtils::replaceNode(node, lhs_node);
      change = true;
    }
  }
  

  return change;
}

