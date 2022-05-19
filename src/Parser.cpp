#include "Parser.hpp"

stem::Parser::Parser()
    : m_token_stream(),
      m_itr(),
      m_end()
{}

stem::Parser::~Parser()
{}

void stem::Parser::factor()
{
  switch (m_itr->m_type)
  {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      break;
    case TokenType::PLUS:
    case TokenType::MINUS:
      break;
    case TokenType::LPAREN:
      break;
  }
}

void stem::Parser::term()
{

}

void stem::Parser::expr()
{

}

bool stem::Parser::parse(std::list<stem::Token> *token_stream)
{
  // initialize member variables
  m_token_stream = token_stream;
  m_itr = m_token_stream->begin();
  m_end = m_token_stream->end();

  if (m_itr != m_end) // if token stream isn't empty
  {
    // TODO parse single token

    

    // end of parse
    ++m_itr;
  }
}