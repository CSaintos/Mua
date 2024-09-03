#include "Parser.hpp"

using namespace std;
using namespace stem;

Parser::Parser()
    : last_op(TokenType::EMPTY),
      last_type(TokenType::EMPTY),
      paren_count(0)
{}

Parser::~Parser()
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
    serr.setDetails("Encountered a value after a value");
    break;
  default:
    break;
  }

  cout << serr.to_string() << endl;

  exit(1);
}

void Parser::addExclusiveParent(Node *node)
{
  if (node->isExclusiveParent())
  {
    node_queue.push(node);
  }
}

void Parser::buildUnaLOp()
{
  // Extract nodes
  if (!node_stack.empty() && right_node == nullptr)
  {
    right_node = std::move(node_stack.top());
    node_stack.pop();
  } 
  else if (node_stack.empty() && right_node == nullptr)
  {
    //! Error
    err(1, *itr);
  }

  if (!node_stack.empty() && op_node == nullptr)
  {
    op_node = std::move(node_stack.top());
    node_stack.pop();
  }
  else
  {
    //! Error
    err(0, *itr);
  }

  // build tree branch
  right_node = std::make_unique<UnaOpNode>(op_node, right_node);
  // If node is an exclusive parent, add it
  addExclusiveParent(&(*right_node));
}

void Parser::buildUnaROp()
{
  // Extract nodes
  if (op_node == nullptr)
  {
    op_node = std::move(node_stack.top());
    node_stack.pop();
  }
  else
  {
    //! Error
    err(0, *itr);
  }

  if (!node_stack.empty() && right_node == nullptr)
  {
    right_node = std::move(node_stack.top());
    node_stack.pop();
  }
  else if (node_stack.empty() && right_node == nullptr)
  {
    //! Error
    err(1, *itr); // expected 1 or d
  }

  // build tree branch
  right_node = std::make_unique<UnaOpNode>(op_node, right_node);
  // If node is an exclusive parent, add it
  addExclusiveParent(&(*right_node));
}

void Parser::buildBinOp()
{
  // Extract nodes
  if (right_node == nullptr)
  {
    right_node = std::move(node_stack.top());
    node_stack.pop();
  }

  if (!node_stack.empty())
  {
    op_node = std::move(node_stack.top());
    node_stack.pop();
  }
  else
  {
    op_node.reset();
  }

  if (!node_stack.empty())
  {
    left_node = std::move(node_stack.top());
    node_stack.pop();
  }
  else if (op_node != nullptr)
  {
    if (curr_node != nullptr)
    {
      left_node = std::move(curr_node);
    }
    else
    {
      //! Error
      err(1, *itr); // expected d or i
    }
  }
  
  // Build tree branch
  if (left_node != nullptr)
  {
    right_node = std::make_unique<BinOpNode>(left_node, op_node, right_node);
    // If node is an exclusive parent, add it
    addExclusiveParent(&(*right_node));
  }
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
      addExclusiveParent(&(*right_node));
      //if (node_stack.size() > 2 ||
      //    (node_stack.size() == 2 && curr_node != nullptr))
      //{
      //  buildBinOp();
      //}
      //else if (node_stack.size() == 2)
      //{
      //  buildUnaLOp();
      //}
      //else if (node_stack.size() == 1)
      //{
      //  right_node = std::move(node_stack.top());
      //  node_stack.pop();
      //}
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
        break;
      }
      switch (op_node->m_tok.type)
      {
      case TokenType::PLUS:
      case TokenType::MINUS:
        right_node = std::make_unique<UnaOpNode>(op_node, right_node);
        addExclusiveParent(&(*right_node));
        break;
      default:
        err(0, *itr);
        break;
      }
      break;
//      if (right_node != nullptr)
//      {
//        if (node_stack.size() > 1)
//        {
//          buildBinOp();
//        }
//        else if (node_stack.size() == 1)
//        {
//          buildUnaLOp();
//        }
//        else
//        {
//          err(0, *itr);
//        }
//      }
//      else
//      {
//        err(0, *itr); //? don't know when this happens
//        //buildUnaOp();
//      }
//      break;
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
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
//      if (right_node != nullptr)
//      {
//        buildBinOp();
//      }
//      else
//      {
//        //! Error
//        err(1, *itr); // expected d or 1
//      }
      break;
    case TokenType::LPAREN:
      unaop_node = dynamic_cast<UnaOpNode*>(node_stack.top().get());
      if (unaop_node->m_node == nullptr)
      {
        if (right_node != nullptr)
        {
          node_stack.push(std::move(right_node));
        }
        loop = false;
      }
      // TODO check if parenthesis contains a node
      // If it doesn't contain a node, reinsert right node (if not empty) into stack and break loop
      //? else apply binary operation
      break;
    default:
      //! Error
      err(1, *itr); // expected d or i
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
    addExclusiveParent(&(*curr_node));
  }
}

void Parser::scanOneToken()
{
  switch (itr->type)
  {
  case TokenType::DIGIT:
  case TokenType::IDENTIFIER:
    switch (last_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      switch (last_op)
      {
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
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
      default:
        err(0, *itr); // unknown error
        break;
      }
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
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
        break;
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        // empty stack and build tree
        toParseTree();
        // add token to stack
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
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
    switch (last_type)
    {
    case TokenType::EMPTY:
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
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
        break;
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        toParseTree();
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
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
      case TokenType::CARET:
        last_type = itr->type;
        last_op = last_type;
        node_stack.push(std::make_unique<BinOpNode>(*itr));
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
    case TokenType::CARET:
    case TokenType::RPAREN:
      last_type = itr->type;
      last_op = last_type;
      node_stack.push(std::make_unique<UnaOpNode>(*itr));
      paren_count++;
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
      err(0, *itr); // not a valid stmt
      break;
    default:
      switch (last_op)
      {
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
      case TokenType::LPAREN:
        // empty stack and build tree
        toParseTree();
        // attach resulting node to LPAREN node
        buildUnaLOp();
        // add nodes to tree
        toParseTree();
        // label last token
        last_type = itr->type;
        last_op = last_type;
        paren_count--;
        break;
      default:
        //? Error
        err(0, *itr); // unknown
        break;
      }
      break;
    }
    break;
  default:
    // TODO throw unknown syntax error
    err(0, *itr);
    break;
  }
}

void Parser::parse(list<Token> *token_stream)
{
  // initialize member variables
  token_stream = token_stream;
  curr_node.reset(); //? is this a good idea?
  
  for (itr = token_stream->begin(); itr != token_stream->end(); ++itr)
  {
    //std::cout << (*m_itr).to_string() << std::endl;
    scanOneToken();
  }

  toParseTree();
}

Node* Parser::getParseTree()
{
  if (curr_node == nullptr)
    return nullptr;
  return &(*curr_node);
}
