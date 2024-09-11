#include "Parser.hpp"

using namespace std;
using namespace stem;

Parser::Parser()
  : last_op(TokenType::EMPTY),
    last_type(TokenType::EMPTY),
    open_parens(),
    equal_count(0),
    let_stmt(false),
    right_paren(false),
    end_of_expr(false),
    end_of_stmt(false)
{}

void Parser::err(int i, Token &tok)
{
  Error serr;
  serr.setPos(tok.pos);
  serr.setName("Syntax Error");
  serr.setDetails("Undefined");

  switch (i)
  {
  case 1:
    serr.setDetails("Expected a DIGIT or IDENTIFIER");
    break;
  case 2:
    serr.setDetails("Unclosed LPAREN, expected an RPAREN after LPAREN but before " + tok.to_string());
    break;
  case 3:
    serr.setDetails("Can't enclose EQUAL between parenthesis (LPAREN, RPAREN)");
    break;
  case 4:
    serr.setDetails("LET keyword must be first in a statement. Syntax: LET IDENTIFIER = <expr>;");
    break;
  case 5:
    serr.setDetails("LetStmt can only have one '='");
    break;
  case 6:
    serr.setDetails("LET keyword must be followed by a single IDENTIFIER. Syntax: LET IDENTIFIER = <expr>;");
    break;
  default:
    break;
  }

  cout << serr.to_string() << endl;

  exit(1);
}

void Parser::propagateTree()
{
  parse_trees.push_back(std::move(curr_node));
  last_type = TokenType::EMPTY;
  last_op = TokenType::EMPTY;
  open_parens = stack<Node*>();
  equal_count = 0;
  let_stmt = false;
  right_paren = false;
  end_of_expr = false;
  end_of_stmt = false;
}

void Parser::toParseTree()
{
  bool loop = true;
  while (!node_stack.empty() && loop)
  {
    TokenType type_top = node_stack.top()->m_tok.type;

    switch (type_top)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::ADJACENT:
      if (right_node == nullptr)
      {
        right_node = std::move(node_stack.top());
        node_stack.pop();
        break;
      }
      left_node = std::move(node_stack.top());
      node_stack.pop();
      if (op_node == nullptr)
      {
        Token place_holder;
        place_holder.type = TokenType::ADJACENT;
        op_node = std::make_unique<BinOpNode>(place_holder);  
      }
      right_node = std::make_unique<BinOpNode>(left_node, op_node, right_node);
      break;
    case TokenType::PLUS:
    case TokenType::MINUS:
      if (right_node == nullptr)
      {
        err(0, *itr);
        break;
      }
      if (op_node == nullptr)
      {
        op_node = std::move(node_stack.top());  
        node_stack.pop();
        if (op_node->getType() == NodeType::UNARY_OPERATOR)
        {
          right_node = std::make_unique<UnaOpNode>(op_node, right_node);
        }
        break;
      }
      left_node = std::move(node_stack.top());
      node_stack.pop();
      right_node = std::make_unique<BinOpNode>(left_node, op_node, right_node);
      break;
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::CARET:
      if (right_node == nullptr)
      {
        err(0, *itr);
        break;
      }
      if (op_node == nullptr)
      {
        op_node = std::move(node_stack.top());
        node_stack.pop();
        break;
      }
      else 
      {
        err(0, *itr);
        break;
      }
      break;
    case TokenType::LPAREN:
      unaop_node = dynamic_cast<UnaOpNode*>(node_stack.top().get());
      if (unaop_node->m_node == nullptr)
      {
        if (right_paren)
        {
          op_node = std::move(node_stack.top());
          node_stack.pop();
          right_paren = false;
          if (right_node == nullptr)
          {
            Token place_holder;
            right_node = std::make_unique<ValueNode>(place_holder);
          }
          right_node = std::make_unique<UnaOpNode>(op_node, right_node);
        }
        else
        {
          if (right_node != nullptr)
          {
            node_stack.push(std::move(right_node));
          }
          loop = false;
        }
      }
      else 
      {
        if (right_node == nullptr)
        {
          right_node = std::move(node_stack.top());
          node_stack.pop();
        }
        else
        {
          err(0, node_stack.top()->m_tok);
        }
      }
      break;
    case TokenType::RPAREN:
      right_paren = true;
      node_stack.pop();
      break;
    case TokenType::EQUAL:
      if (right_node == nullptr)
      {
        err(1, *itr);
        break;
      }
      if (!end_of_expr)
      {
        node_stack.push(std::move(right_node));
        loop = false;
        break;  
      }
      if (open_parens.size() != 0)
      {
        err(3, open_parens.top()->m_tok);
        break;
      }
      op_node = std::move(node_stack.top());
      node_stack.pop();
      if (node_stack.size() != 0)
      {
        left_node = std::move(node_stack.top());
        node_stack.pop();
        right_node = std::make_unique<BinOpNode>(left_node, op_node, right_node);
      }
      else if (curr_node != nullptr)
      {
        right_node = std::make_unique<BinOpNode>(curr_node, op_node, right_node);
      }
      else 
      {
        err(0, op_node->m_tok);
        break;
      }
      break;
    case TokenType::LET:
      if (right_node == nullptr)
      {
        err(6, *itr);
        break;
      }
      if (!end_of_expr)
      {
        node_stack.push(std::move(right_node));
        loop = false;
        break;
      }
      op_node = std::move(node_stack.top());
      node_stack.pop();
      right_node = std::make_unique<UnaOpNode>(op_node, right_node);
      break;
    case TokenType::SEMICOLON:
      if (node_stack.size() == 1)
      {
        end_of_stmt = true;
        op_node = std::move(node_stack.top());
        node_stack.pop();
      }
      else
      {
        if (open_parens.size() != 0)
        {
          err(2, open_parens.top()->m_tok);
        }
        else
        {
          err(0, *itr);
        }
      }
      break;
    default:
      //! Error
      err(1, *itr); // expected d or i
      break;
    }
  }

  if (curr_node == nullptr && right_node != nullptr)
  {
    curr_node = std::move(right_node);
  }
  if (right_node != nullptr)
  {
    if (op_node == nullptr)
    {
      Token place_holder;
      place_holder.type = TokenType::ADJACENT;
      op_node = std::make_unique<BinOpNode>(place_holder);
    }
    curr_node = std::make_unique<BinOpNode>(curr_node, op_node, right_node);
  }
  if (end_of_stmt && op_node != nullptr)
  {
    if (curr_node == nullptr) 
    {
      Token place_holder;
      curr_node = std::make_unique<ValueNode>(place_holder);
    }
    curr_node = std::make_unique<UnaOpNode>(op_node, curr_node);
  }
}

void Parser::scanOneToken()
{
  switch (itr->type)
  {
  case TokenType::IDENTIFIER:
    if (last_type == TokenType::LET)
    {
      last_type = itr->type;
      node_stack.push(std::make_unique<ValueNode>(*itr));
      break;
    }
  case TokenType::DIGIT:
    switch (last_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      switch (last_op)
      {
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::PERCENT:
      case TokenType::CARET:
        toParseTree();
        last_type = itr->type;
        last_op = TokenType::ASTERISK;
        node_stack.push(std::make_unique<ValueNode>(*itr));
        break;
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
      case TokenType::PLUS:
      case TokenType::MINUS:
        last_type = itr->type;
        last_op = TokenType::ASTERISK;
        node_stack.push(std::make_unique<ValueNode>(*itr));
        break;
      case TokenType::LET:
        err(6, *itr);
      default:
        err(0, *itr); // unknown error
        break;
      }
      break;
    case TokenType::LET:
      err(6, *itr);
      break;
    default:
      last_type = itr->type;
      node_stack.push(std::make_unique<ValueNode>(*itr));
      break;
    }
    break;
  case TokenType::MINUS:
  case TokenType::PLUS:
    switch (last_type)
    {
    case TokenType::EMPTY:
    case TokenType::LPAREN:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::EQUAL:
      last_type = itr->type;
      last_op = last_type;
      node_stack.push(std::make_unique<UnaOpNode>(*itr));
      break;
    default:
      switch (last_op)
      {
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
      case TokenType::EQUAL:
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
        break;
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::PERCENT:
      case TokenType::CARET:
        // empty stack and build tree
        toParseTree();
        // add token to stack
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
        break;
      case TokenType::LET:
        err(6, *itr);
        break;
      default:
        // error
        err(0, *itr); // unknown
        break;
      }
      break;
    }
    break;
  case TokenType::FSLASH:
  case TokenType::ASTERISK:
  case TokenType::PERCENT:
    switch (last_type)
    {
    case TokenType::EMPTY:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::FSLASH:
    case TokenType::ASTERISK:
    case TokenType::PERCENT:
    case TokenType::EQUAL:
      //! Error
      err(1, *itr); // expected d or i
      break;
    default:
      switch (last_op)
      {
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::EQUAL:
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
        break;
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
      case TokenType::PERCENT:
        toParseTree();
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
        break;
      case TokenType::LET:
        err(6, *itr);
        break;
      default:
        // error unknown
        err(0, *itr);
        break;
      }
      break;
    }
    break;
  case TokenType::CARET:
    switch (last_type)
    {
    case TokenType::EMPTY:
    case TokenType::CARET:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::MINUS:
    case TokenType::PLUS:
    case TokenType::LPAREN:
    case TokenType::EQUAL:
      //! Error
      err(1, *itr); // expected d or i
      break;
    default:
      switch (last_op)
      {
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::PERCENT:
      case TokenType::CARET:
      case TokenType::EQUAL:
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
        break;
      case TokenType::LET:
        err(6, *itr);
        break;
      default:
        err(0, *itr);
        break;
      }
      break;
    }
    break;
  case TokenType::LPAREN:
    switch (last_op)
    {
    case TokenType::EMPTY:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::CARET:
    case TokenType::RPAREN:
    case TokenType::EQUAL:
      last_type = itr->type;
      last_op = last_type;
      node_stack.push(std::make_unique<UnaOpNode>(*itr));
      open_parens.push(node_stack.top().get());
      break;
    case TokenType::LET:
      err(6, *itr);
      break;
    default:
      err(0, *itr); // unknown
      break;
    }
    break;
  case TokenType::RPAREN:
    switch (last_type)
    {
    case TokenType::EMPTY:
      err(1, *itr); // not a valid stmt
      break;
    default:
      switch (last_op)
      {
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::PERCENT:
      case TokenType::CARET:
      case TokenType::LPAREN:
        node_stack.push(std::make_unique<UnaOpNode>(*itr));
        toParseTree();
        last_type = itr->type;
        last_op = last_type;
        open_parens.pop();
        break;
      case TokenType::EQUAL:
        err(3, *itr);
        break;
      default:
        //? Error
        err(0, *itr); // unknown
        break;
      }
      break;
    }
    break;
  case TokenType::EQUAL:
    switch (last_type)
    {
    case TokenType::RPAREN:
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      if (let_stmt && equal_count > 0)
      {
        err(5, *itr);
        break;
      }
      toParseTree();
      node_stack.push(std::make_unique<BinOpNode>(*itr));
      last_type = itr->type;
      last_op = last_type;
      equal_count++;
      break;
    default:
      err(1, *itr);
      break;
    }
    break;
  case TokenType::LET:
    switch (last_type)
    {
    case TokenType::EMPTY:
      node_stack.push(std::make_unique<UnaOpNode>(*itr));
      last_type = itr->type;
      last_op = last_type;
      let_stmt = true;
      break;
    default:
      err(4, *itr);
      break;
    }
    break;
  case TokenType::SEMICOLON:
    switch (last_type)
    {
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::CARET:
    case TokenType::EQUAL:
      err(1, *itr);
      break;
    case TokenType::LET:
      err(6, *itr);
      break;
    default:
      end_of_expr = true;
      toParseTree();
      node_stack.push(std::make_unique<UnaOpNode>(*itr));
      toParseTree();
      propagateTree();
      break;
    }
    break;
  default:
    err(0, *itr);
    break;
  }
}

void Parser::parse(list<Token> *token_stream)
{
  // initialize member variables
  token_stream = token_stream;
  
  for (itr = token_stream->begin(); itr != token_stream->end(); ++itr)
  {
    //std::cout << (*m_itr).to_string() << std::endl;
    scanOneToken();
  }
}

//vector<Node*> Parser::getParseTrees()
//{
//  vector<Node*> parse_tree_pointers;
//  for (int i = 0; i < parse_trees.size(); i++)
//  {
//    parse_trees[i].get();
//  }
//}
