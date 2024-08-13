#include "Token.hpp"

using namespace std;
using namespace stem;

Token::Token()
{
  init();
}

Token::Token(const Token &tok)
  : type(tok.type),
    lexemes(tok.lexemes),
    pos(tok.pos)
{}

void Token::init()
{
  type = TokenType::EMPTY;
  lexemes = "";
  pos.init();
}

string Token::to_string()
{
  string output = "";

  if (type == TokenType::DIGIT || type == TokenType::IDENTIFIER)
  {
    output = TokenUtils::m_TS_map[type] + ":" + lexemes;
  }
  else
  {
    output = TokenUtils::m_TS_map[type];
  }

  return output;
}
