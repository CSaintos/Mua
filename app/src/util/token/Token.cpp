#include "token.hpp"

stem::Token::Token()
{
  init();
}

stem::Token::Token(const Token &tok)
    : m_type(tok.m_type),
      m_lexemes(tok.m_lexemes),
      m_pos(tok.m_pos)
{}

void stem::Token::init()
{
  m_type = stem::TokenType::EMPTY;
  m_lexemes = "";
  m_pos.init();
}

std::string stem::Token::to_string()
{
  std::string output = "";

  if (m_type == TokenType::DIGIT || m_type == TokenType::IDENTIFIER)
  {
    output = TokenUtils::m_TS_map[m_type] + ":" + m_lexemes;
  }
  else
  {
    output = TokenUtils::m_TS_map[m_type];
  }

  return output;
}
