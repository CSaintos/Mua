#include "Lexer.hpp"

using namespace std;
using namespace stem;

Lexer::Lexer()
    : char_list(),
      itr(),
      end()
{}

Lexer::~Lexer()
{
  token_stream.clear();
  ss.clear();
}

void Lexer::init(list<Character> *char_list)
{
  char_list = char_list;
  itr = char_list->begin();
  end = char_list->end();
  token_temp.init();
  token_stream.clear();
  ss.str(string());
}

TokenType Lexer::charToTokenType(char &ch)
{
  TokenType type = TokenType::UNKNOWN;

  // if char exists in RT map
  if (TokenUtils::m_RT_map.find(string(1, ch)) != TokenUtils::m_RT_map.end())
  {
    type = TokenUtils::m_RT_map[string(1, ch)];
  }

  return type;
}

void Lexer::err(Character &c)
{
  Error err(c.pos, "IllegalCharError", "'" + c.to_string() + "'");
  cout << err.to_string() << endl;
  exit(1);
}

void Lexer::toTokenStream()
{
  if (TokenUtils::m_RT_map.find(ss.str()) != TokenUtils::m_RT_map.end())
      token_temp.m_type = TokenUtils::m_RT_map[ss.str()];
  token_temp.m_lexemes = ss.str();
  token_stream.push_back(token_temp);

  token_temp.init();
  ss.str(string());
}

void Lexer::createToken(TokenType &type, Character &c)
{
  token_temp.m_type = type;
  token_temp.m_pos = c.pos;
  ss << c.c;
}

void Lexer::scanOneChar(Character &c)
{
  TokenType type = charToTokenType(c.c);

  // FIXME implement a more clean solution
  switch (type)
  {
  case TokenType::SPACE:
    switch (token_temp.m_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::PERCENT:
    case TokenType::CARET:
    case TokenType::RPAREN:
    case TokenType::EQUAL:
    case TokenType::EXCLAMATION:
    case TokenType::LESSTHAN:
    case TokenType::MORETHAN:
    case TokenType::COMMA:
    case TokenType::VSLASH:
      toTokenStream();
      token_temp.m_type = type;
      break;
    case TokenType::SPACE:
      break;
    default:
      err(c);
    }
    break;
  case TokenType::SEMICOLON:
    switch (token_temp.m_type)
    {
    case TokenType::IDENTIFIER:
    case TokenType::DIGIT:
    case TokenType::RPAREN:
    case TokenType::RBRACE:
    case TokenType::RBRACKET:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::COLON:
    err(c);
    break;
  case TokenType::LPAREN:
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, c);
      break;
    case TokenType::IDENTIFIER:
    case TokenType::LPAREN:
    case TokenType::RBRACKET:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::CARET:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::RPAREN:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, c);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::LBRACKET:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::RBRACKET:
    switch (token_temp.m_type)
    {
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::LBRACE:
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::RBRACE:
    switch (token_temp.m_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::AMPERSAND:
    err(c);
    break;
  case TokenType::VSLASH:
    switch(token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::TILDE:
    err(c);
    break;
  case TokenType::EQUAL:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, c);
      break;
    case TokenType::IDENTIFIER:
    case TokenType::DIGIT:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::LESSTHAN:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
    case TokenType::DIGIT:
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::MORETHAN:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
    case TokenType::DIGIT:
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::EXCLAMATION:
    switch (token_temp.m_type)
    {
    case TokenType::DIGIT:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::COMMA:
    switch (token_temp.m_type)
    {
    case TokenType::DIGIT:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::DOT:
    switch (token_temp.m_type)
    {
    case TokenType::DIGIT:
      if (dot_count > 1)
      {
        Error err(c.pos, "IllegalCharError", "DIGIT already has DOT '.'");
        cout << err.to_string() << endl;
        exit(1);
      }
      else
      {
        ss << c.c;
        ++dot_count;
      }
      break;
    default:
      err(c);
    }
    break;
  case TokenType::PLUS:
  case TokenType::MINUS:
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, c);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::ASTERISK:
  case TokenType::PERCENT:
  case TokenType::CARET:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, c);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::FSLASH:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
    case TokenType::EMPTY:
      createToken(type, c);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, c);
      break;
    case TokenType::FSLASH:
      ss << c.c;
      if (TokenType::COMMENT == TokenUtils::m_RT_map[ss.str()])
      {
        token_temp.m_type = TokenType::COMMENT;
      }
      break;
    default:
      err(c);
    }
    break;
  case TokenType::UNDERSCORE:
    switch (token_temp.m_type)
    {
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
  case TokenType::DIGIT:
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, c);
      dot_count = 0;
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      ss << c.c;
      break;
    case TokenType::LPAREN:
    case TokenType::ASTERISK:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::CARET:
    case TokenType::EQUAL:
      toTokenStream();
      createToken(type, c);
      dot_count = 0;
      break;
    default:
      err(c);
    }
    break;
  case TokenType::IDENTIFIER:
    switch (token_temp.m_type)
    {
    case TokenType::PERCENT:
    case TokenType::FSLASH:
    case TokenType::ASTERISK:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::CARET:
    case TokenType::UNDERSCORE:
    case TokenType::LPAREN:
    case TokenType::LBRACE:
    case TokenType::LBRACKET:
    case TokenType::EQUAL:
      toTokenStream();
      createToken(type, c);
      break;
    case TokenType::SPACE:
    case TokenType::EMPTY:
      createToken(type, c);
      break;
    case TokenType::IDENTIFIER:
      ss << c.c;
      break;
    default:
      err(c);
    }
    break;
  default:
    err(c);
    break;
  }
}

bool Lexer::lex(list<Character> *char_list)
{
  //* initialize variables
  init(char_list);
  //* check char list size
  if (char_list->size() == 0) return false;

  //* iterate through char list and convert to token stream
  while (itr != end)
  {
    //std::cout << "char: " << *m_itr << " ";
    scanOneChar(*itr);
    //std::cout << "ss: " << ((ss.str().length() == 0) ? "(null)" : ss.str()) << std::endl;

    ++itr;
  }

  //* Add last remaining token to stream
  if (token_temp.m_type != TokenType::EMPTY &&
      token_temp.m_type != TokenType::SPACE)
  {
    if (token_temp.m_type != TokenType::COMMENT)
    {
      toTokenStream();
    }
    else 
    {
      token_temp.init();
      ss.str(string());
    }
  }
  return true;
}

list<Token> *Lexer::getList()
{
  return &token_stream;
}
