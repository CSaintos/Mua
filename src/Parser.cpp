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

void stem::Parser::factor()
{
  switch (m_itr->m_type)
  {
    case TokenType::DIGIT:
      m_curr_node = std::make_unique<DigitNode>(*m_itr);
      break;
    case TokenType::IDENTIFIER:
      m_curr_node = std::make_unique<IdentifierNode>(*m_itr);
      break;
    case TokenType::PLUS:
    case TokenType::MINUS:
      m_curr_node = std::make_unique<UnaOpNode>(*m_itr, m_curr_node);
      break;
    case TokenType::LPAREN:
      break;
  }
}

void stem::Parser::term()
{
  switch (m_itr->m_type)
  {
  case TokenType::FSLASH:
  case TokenType::ASTERISK:
    m_left_node = std::move(m_curr_node);
    m_tok_op = *m_itr;
    advance();
    factor();
    m_right_node = std::move(m_curr_node);
    m_curr_node = std::make_unique<BinOpNode>(m_left_node, m_tok_op, m_right_node);
    break;
  default:
    factor();
  }
}

void stem::Parser::expr()
{
  switch (m_itr->m_type)
  {
  case TokenType::PLUS:
  case TokenType::MINUS:
    m_left_node = std::move(m_curr_node);
    m_tok_op = *m_itr;
    advance();
    term(); // the only difference
    // TODO need to check ahead, then go back, then move forward
    
    // end of TODO
    m_right_node = std::move(m_curr_node);
    m_curr_node = std::make_unique<BinOpNode>(m_left_node, m_tok_op, m_right_node);
    break;
  default:
    term();
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
      //! Error
      std::cout << "Encountered a value after a value" << std::endl;
      break;
    default:
      m_last_type = m_itr->m_type;
      m_node_stack.push(DigitNode(*m_itr));
      break;
    }
    break;
  case TokenType::IDENTIFIER:
    switch (m_last_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      //! Error
      std::cout << "Encountered a value after a value" << std::endl;
      break;
    default:
      m_last_type = m_itr->m_type;
      m_node_stack.push(IdentifierNode(*m_itr));
      break;
    }
    break;
  case TokenType::FSLASH:
  case TokenType::ASTERISK:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      //! Error
      std::cout << "Expected a DIGIT or IDENTIFIER" << std::endl;
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(BinOpNode(*m_itr));
        break;
      }
    }
    break;
  case TokenType::MINUS:
  case TokenType::PLUS:
    break;

  }
  m_node_stack.push(DigitNode(*m_itr));
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
}

stem::Node* stem::Parser::getParseTree()
{
  if (m_curr_node == nullptr)
    return nullptr;
  return &(*m_curr_node);
}
