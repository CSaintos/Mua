#include "Parser.hpp"

stem::Parser::Parser()
    : m_last_op(TokenType::EMPTY),
      m_last_type(TokenType::EMPTY)
{}

stem::Parser::~Parser()
{}

void stem::Parser::advance()
{
  if (m_itr != m_end)
  {
    ++m_itr;
  }
}

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
}

void stem::Parser::buildBinOp()
{
  // Extract nodes
  if (m_right_node == nullptr)
  {
    m_right_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }

  //? assuming ...
  m_tok_op = *(m_node_stack.top()->m_tok);
  m_node_stack.pop();

  //? We're assuming that we have nodes left to pop
  m_left_node = std::move(m_node_stack.top());
  m_node_stack.pop();

  // Build tree branch
  m_right_node = std::make_unique<BinOpNode>(m_left_node, m_tok_op, m_right_node);
}

void stem::Parser::toParseTree()
{
  while (!m_node_stack.empty())
  {
    switch (m_node_stack.top()->m_tok->m_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      buildBinOp();
      break;
    
    default:
      //! Error
      err(1); // expected d or i
    }
  }
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
      //? Error May not happen
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
      //? Error May not happen
      err(2); // value after value err
      break;
    default:
      m_last_type = m_itr->m_type;
      m_node_stack.push(std::make_unique<IdentifierNode>(*m_itr));
      break;
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
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      default:
        // TODO empty stack and build tree
      }
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
      case TokenType::FSLASH:
      case TokenType::ASTERISK:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      default:
        // TODO empty stack and build tree
      }
    }
    break;
  default:
    // TODO throw unknown syntax error
  }
}

void stem::Parser::parse(std::list<stem::Token> *token_stream)
{
  // initialize member variables
  m_token_stream = token_stream;
  m_itr = m_token_stream->begin();
  m_end = m_token_stream->end();
  m_curr_node = nullptr;

  while (m_itr != m_end) // if token stream isn't empty
  {
    // TODO parse single token
    scanOneToken();
    // end of parse
    advance();
  }
  toParseTree();
}

stem::Node* stem::Parser::getParseTree()
{
  if (m_curr_node == nullptr)
    return nullptr;
  return &(*m_curr_node);
}
