#include "Parser.hpp"

stem::Parser::Parser()
    : m_last_op(TokenType::EMPTY),
      m_last_type(TokenType::EMPTY)
{}

stem::Parser::~Parser()
{}

void stem::Parser::err(int i)
{
  switch (i)
  {
  case 1:
    std::cout << "Syntax Err: Expected a DIGIT or IDENTIFIER" << std::endl;
    break;
  case 2:
    std::cout << "Syntax Err: Encountered a value after a value" << std::endl;
    break;
  default:
    std::cout << "Syntax Err: Undefined" << std::endl;
  }
  exit(1);
}

void stem::Parser::buildUnaOp()
{
  // Extract nodes
  if (m_op_node == nullptr)
  {
    m_op_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }

  if (!m_node_stack.empty() && m_right_node == nullptr)
  {
    m_right_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else if (m_node_stack.empty() && m_right_node == nullptr)
  {
    //! Error
    err(1); // expected 1 or d
  }

  // build tree branch
  m_right_node = std::make_unique<UnaOpNode>(m_op_node, m_right_node);
}

void stem::Parser::buildBinOp()
{
  // Extract nodes
  if (m_right_node == nullptr)
  {
    m_right_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }

  if (!m_node_stack.empty())
  {
    m_op_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else
  {
    m_op_node.release();
  }

  if (!m_node_stack.empty())
  {
    m_left_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else if (m_op_node != nullptr)
  {
    if (m_curr_node != nullptr)
    {
      m_left_node = std::move(m_curr_node);
    }
    else
    {
      //! Error
      err(1); // expected d or i
    }
  }
  
  // Build tree branch
  if (m_left_node != nullptr)
  {
    m_right_node = std::make_unique<BinOpNode>(m_left_node, m_op_node, m_right_node);
  }
}

void stem::Parser::toParseTree()
{
  while (!m_node_stack.empty())
  {
    TokenType type_top = m_node_stack.top()->m_tok->m_type;

    switch (type_top)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      buildBinOp();
      break;
    case TokenType::PLUS:
    case TokenType::MINUS:
      if (m_right_node != nullptr)
      {
        buildBinOp();
      }
      else
      {
        buildUnaOp();
      }
      break;
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::CARET:
      if (m_right_node != nullptr)
      {
        buildBinOp();
      }
      else
      {
        //! Error
        err(1); // expected d or 1
      }
    default:
      //! Error
      err(1); // expected d or i
    }
  }
  m_curr_node = std::move(m_right_node);
}

void stem::Parser::scanOneToken()
{
  switch (m_itr->m_type)
  {
  case TokenType::DIGIT:
    switch (m_last_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      //! Error
      err(2); // value after value err
      break;
    default:
      m_last_type = m_itr->m_type;
      m_node_stack.push(std::make_unique<DigitNode>(*m_itr));
      break;
    }
    break;
  case TokenType::IDENTIFIER:
    switch (m_last_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      //! Error
      err(2); // value after value err
      break;
    default:
      m_last_type = m_itr->m_type;
      m_node_stack.push(std::make_unique<IdentifierNode>(*m_itr));
      break;
    }
    break;
  case TokenType::MINUS:
  case TokenType::PLUS:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      // TODO write unary operator case
      err(1); // expected d or i
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        // empty stack and build tree
        toParseTree();
        // add token to stack
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      default:
        // error
        err(0); // unknown
      }
    }
    break;
  case TokenType::FSLASH:
  case TokenType::ASTERISK:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      //! Error
      err(1); // expected d or i
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
      case TokenType::PLUS:
      case TokenType::MINUS:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        // empty stack and build tree
        toParseTree();
        // add token to stack
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
      default:
        // error unknown
        err(0);
      }
    }
    break;
  case TokenType::CARET:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      //! Error
      err(1); // expected d or i
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      default:
        // TODO implement parantheses case
        err(0);
      }
    }
    break;
  default:
    // TODO throw unknown syntax error
    err(0);
  }
}

void stem::Parser::parse(std::list<stem::Token> *token_stream)
{
  // initialize member variables
  m_token_stream = token_stream;
  m_curr_node.release();
  
  for (m_itr = token_stream->begin(); m_itr != token_stream->end(); ++m_itr)
  {
    // parse single token
    scanOneToken();
    // end of parse
  }

  toParseTree();
}

stem::Node* stem::Parser::getParseTree()
{
  if (m_curr_node == nullptr)
    return nullptr;
  return &(*m_curr_node);
}
