#include "Parser.hpp"

using namespace std;
using namespace mua;

Parser::Parser()
  : pemd({TokenType::ASTERISK, TokenType::ADJACENT, TokenType::FSLASH, TokenType::PERCENT, TokenType::CARET, TokenType::LPAREN}),
    pe({TokenType::CARET, TokenType::LPAREN}),
    last_op(TokenType::EMPTY),
    last_type(TokenType::EMPTY),
    open_parens(),
    equal_count(0),
    let_stmt(false),
    right_paren(false),
    end_of_expr(false),
    end_of_stmt(false),
    node_factory(std::make_unique<NodeFactory>())
{}

void Parser::err(int i, Token &tok)
{
  Error serr(
    tok.pos, 
    "SyntaxError",
    "Undefined"
  );

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
  case 7:
    serr.setDetails(tok.to_string() + " cannot be rhs ADJACENT to RPAREN. Either explicitly use multiplication operator (ASTERISK) or (implicit multiplication) make it lhs ADJACENT.");
  case 8:
    serr.setDetails("Expected SEMICOLON after " + tok.to_string());
  default:
    break;
  }

  cout << serr.to_string() << endl;

  // TODO: Determine if program should be canceled or not
  exit(1);
}

void Parser::propagateTree()
{
  parse_trees.push_back(std::move(node_stack.top()));
  node_stack.pop();
  last_type = TokenType::EMPTY;
  last_op = TokenType::EMPTY;
  open_parens = stack<Node*>();
  equal_count = 0;
  let_stmt = false;
  right_paren = false;
  end_of_expr = false;
  end_of_stmt = false;
}

void Parser::toParseTree(TokenType precedence_type)
{
  bool loop = true;
  while (!node_stack.empty() && loop)
  {
    TokenType type_top = node_stack.top()->tok.type;

    switch (type_top)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::ADJACENT:
    {
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
        op_node = node_factory->produceNode(TokenType::ADJACENT);
      }
      BinOpNode* bin_raw = static_cast<BinOpNode*>(op_node.get());
      bin_raw->node_left = std::move(left_node);
      bin_raw->node_left->parent = bin_raw;
      bin_raw->node_right = std::move(right_node);
      bin_raw->node_right->parent = bin_raw;
      op_node->state->setContext(op_node.get());
      right_node = std::move(op_node);
      break;
    }
    case TokenType::PLUS:
    case TokenType::MINUS:
    {
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
          UnaOpNode* una_raw = static_cast<UnaOpNode*>(op_node.get());
          una_raw->node = std::move(right_node);
          una_raw->node->parent = una_raw;
          op_node->state->setContext(op_node.get());
          right_node = std::move(op_node);
        }
        else if (pemd.count(precedence_type) == 1)
        {
          loop = false;
          node_stack.push(std::move(op_node));
        }
        break;
      }
      left_node = std::move(node_stack.top());
      node_stack.pop();
      BinOpNode* bin_raw = static_cast<BinOpNode*>(op_node.get());
      bin_raw->node_left = std::move(left_node);
      bin_raw->node_left->parent = bin_raw;
      bin_raw->node_right = std::move(right_node);
      bin_raw->node_right->parent = bin_raw;
      op_node->state->setContext(op_node.get());
      right_node = std::move(op_node);
      break;
    }
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
        if (pe.count(precedence_type) == 1 && !right_paren)
        {
          loop = false;
          node_stack.push(std::move(op_node));
        }
        break;
      }
      else 
      {
        left_node = std::move(node_stack.top());
        node_stack.pop();
        BinOpNode* bin_raw = static_cast<BinOpNode*>(op_node.get());
        bin_raw->node_left = std::move(left_node);
        bin_raw->node_left->parent = bin_raw;
        bin_raw->node_right = std::move(right_node);
        bin_raw->node_right->parent = bin_raw;
        op_node->state->setContext(op_node.get());
        right_node = std::move(op_node);
        break;
      }
      break;
    case TokenType::LPAREN:
    {
      UnaOpNode* una_raw = static_cast<UnaOpNode*>(node_stack.top().get());
      if (una_raw->node == nullptr)
      {
        if (right_paren)
        {
          op_node = std::move(node_stack.top());
          node_stack.pop();
          right_paren = false;
          if (right_node == nullptr)
          {
            right_node = node_factory->produceNode(TokenType::DIGIT);
          }
          una_raw = static_cast<UnaOpNode*>(op_node.get());
          una_raw->node = std::move(right_node);
          una_raw->node->parent = una_raw;
          op_node->state->setContext(op_node.get());
          right_node = std::move(op_node);
          if (!end_of_expr || !end_of_stmt)
          {
            loop = false;
          }
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
          // This line below might need to go in more specific places in this method, in the case that looping is false and nodes need to be put back in node_stack.
          op_b4_paren.pop();
        }
        else
        {
          if (op_node != nullptr)
          {
            left_node = std::move(node_stack.top());
            node_stack.pop();
            BinOpNode* bin_raw = static_cast<BinOpNode*>(op_node.get());
            bin_raw->node_left = std::move(left_node);
            bin_raw->node_left->parent = bin_raw;
            bin_raw->node_right = std::move(right_node);
            bin_raw->node_right->parent = bin_raw;
            op_node->state->setContext(op_node.get());
            right_node = std::move(op_node);
          } 
          else
          {
            err(7, right_node->tok);
          }
        }
      }
      break;
    }
    case TokenType::RPAREN:
      // TODO might need a revision for something like (1(2));
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
        err(3, open_parens.top()->tok);
        break;
      }
      op_node = std::move(node_stack.top());
      node_stack.pop();
      if (node_stack.size() != 0)
      {
        left_node = std::move(node_stack.top());
        node_stack.pop();
        BinOpNode* bin_raw = static_cast<BinOpNode*>(op_node.get());
        bin_raw->node_left = std::move(left_node);
        bin_raw->node_left->parent = bin_raw;
        bin_raw->node_right = std::move(right_node);
        bin_raw->node_right->parent = bin_raw;
        op_node->state->setContext(op_node.get());
        right_node = std::move(op_node);
      }
      else 
      {
        err(0, op_node->tok);
        break;
      }
      break;
    case TokenType::LET:
    {
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
      UnaOpNode* una_raw = static_cast<UnaOpNode*>(op_node.get());
      una_raw->node = std::move(right_node);
      una_raw->node->parent = una_raw;
      op_node->state->setContext(op_node.get());
      right_node = std::move(op_node);
      break;
    }
    case TokenType::SEMICOLON:
      if (node_stack.size() == 2)
      {
        end_of_stmt = true;
        op_node = std::move(node_stack.top());
        node_stack.pop();
        right_node = std::move(node_stack.top());
        node_stack.pop();
        UnaOpNode* una_op_node = static_cast<UnaOpNode*>(op_node.get());
        una_op_node->node = std::move(right_node);
        una_op_node->node->parent = una_op_node;
        op_node->state->setContext(op_node.get());
        right_node = std::move(op_node);
      }
      else
      {
        if (open_parens.size() != 0)
        {
          err(2, open_parens.top()->tok);
        }
        else
        {
          cout << node_stack.size() << endl;
          cout << "This is err 3" << endl;
          err(0, *itr);
        }
      }
      break;
    default:
      //! Error
      err(1, *itr); // expected digit or identifier
      break;
    }
  }

  if (op_node != nullptr)
  {
    if (right_node == nullptr)
    {
      right_node = node_factory->produceNode(TokenType::DIGIT);
    }
    UnaOpNode* una_op_node = static_cast<UnaOpNode*>(op_node.get());
    una_op_node->node = std::move(right_node);
    una_op_node->node->parent = una_op_node;
    op_node->state->setContext(op_node.get());
    node_stack.push(std::move(op_node));
  }
  if (right_node != nullptr)
  {
    node_stack.push(std::move(right_node));
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
      node_stack.push(node_factory->produceNode(*itr));
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
        toParseTree(TokenType::ADJACENT);
        last_type = itr->type;
        last_op = TokenType::ASTERISK;
        node_stack.push(node_factory->produceNode(*itr));
        break;
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
      case TokenType::PLUS:
      case TokenType::MINUS:
        last_type = itr->type;
        last_op = TokenType::ASTERISK;
        node_stack.push(node_factory->produceNode(*itr));
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
      node_stack.push(node_factory->produceNode(*itr));
      break;
    }
    break;
  case TokenType::MINUS:
  case TokenType::PLUS:
    switch (last_type)
    {
    case TokenType::EMPTY:
    case TokenType::LPAREN:
    case TokenType::CARET:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::EQUAL:
      last_type = itr->type;
      last_op = TokenType::ADJACENT;
      node_stack.push(node_factory->produceNode(*itr, NodeType::UNARY_OPERATOR));
      break;
    default:
      switch (last_op)
      {
      case TokenType::RPAREN:
        if (!op_b4_paren.empty() && pemd.contains(op_b4_paren.top()))
        {
          toParseTree(itr->type);
        }
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::EQUAL:
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(node_factory->produceNode(*itr));
        break;
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::ADJACENT:
      case TokenType::FSLASH:
      case TokenType::PERCENT:
      case TokenType::CARET:
        // empty stack and build tree
        toParseTree(itr->type);
        // add token to stack
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(node_factory->produceNode(*itr));
        break;
      case TokenType::LET:
        err(6, *itr);
        break;
      default:
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
      err(1, *itr); // expected digit or identifier
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
        node_stack.push(node_factory->produceNode(*itr));
        break;
      case TokenType::ASTERISK:
      case TokenType::ADJACENT:
      case TokenType::FSLASH:
      case TokenType::CARET:
      case TokenType::PERCENT:
        toParseTree(itr->type);
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(node_factory->produceNode(*itr));
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
      err(1, *itr); // expected digit or identifier
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
      case TokenType::ADJACENT:
      case TokenType::FSLASH:
      case TokenType::PERCENT:
      case TokenType::CARET:
      case TokenType::EQUAL:
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(node_factory->produceNode(*itr));
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
        toParseTree(TokenType::ADJACENT);
        node_stack.push(node_factory->produceNode(*itr));
        open_parens.push(node_stack.top().get());
        last_type = itr->type;
        last_op = last_type;
        break;
      case TokenType::EMPTY:
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::EQUAL:
      case TokenType::LPAREN:
        op_b4_paren.push(TokenType::ADJACENT);
        node_stack.push(node_factory->produceNode(*itr));
        open_parens.push(node_stack.top().get());
        last_type = itr->type;
        last_op = last_type;
        break;
      case TokenType::LET:
        err(6, *itr);
        break;
      default:
        err(0, *itr);
        break;
      }
      break;
    case TokenType::LET:
      err(6, *itr);
      break;
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::CARET:
    case TokenType::RPAREN:
    case TokenType::LPAREN:
    case TokenType::EQUAL:
      op_b4_paren.push(last_type);
    case TokenType::EMPTY:
      node_stack.push(node_factory->produceNode(*itr));
      open_parens.push(node_stack.top().get());
      last_type = itr->type;
      last_op = last_type;
      break;
    default:
      err(0, *itr);
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
      case TokenType::ADJACENT:
      case TokenType::FSLASH:
      case TokenType::PERCENT:
      case TokenType::CARET:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
        node_stack.push(node_factory->produceNode(*itr));
        toParseTree(itr->type);
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
      toParseTree(itr->type);
      node_stack.push(node_factory->produceNode(*itr));
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
      node_stack.push(node_factory->produceNode(*itr));
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
      toParseTree(itr->type);
      node_stack.push(node_factory->produceNode(*itr));
      toParseTree(itr->type);
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
    //cout << (*itr).to_string() << endl; // DEBUG
    scanOneToken();
  }
}

void Parser::checkSemicolonError()
{
  if (!node_stack.empty())
  {
    err(8, node_stack.top()->tok);
  }
}
