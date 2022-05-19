#include "Parser.hpp"

stem::Parser::Parser()
    : m_token_stream(),
      m_itr(),
      m_end(),
      m_curr_node(),
      m_root_node(),
      m_left_node(),
      m_right_node()
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
    m_root_node = std::make_unique<BinOpNode>(m_left_node, m_tok_op, m_right_node);
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
    // left = unique pointer
    // op_tok = *itr
    // itr++ and we call term()
    // right = unique pointer
    // current_node = BinOpNode(left, op_tok, right)
    break;
  default:
    term();
  }
}

void stem::Parser::parse(std::list<stem::Token> *token_stream)
{
  // initialize member variables
  m_token_stream = token_stream;
  m_itr = m_token_stream->begin();
  m_end = m_token_stream->end();
  m_root_node = nullptr;

  while (m_itr != m_end) // if token stream isn't empty
  {
    // TODO parse single token
    expr();
    // end of parse
    advance();
  }
}

stem::Node* stem::Parser::getParseTree()
{
  if (m_root_node == nullptr)
    return nullptr;
  return &(*m_root_node);
}
