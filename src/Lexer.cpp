#include "Lexer.hpp"

stem::Lexer::Lexer(const std::string &file_name)
    : m_char_list(),
      m_itr(),
      m_end(),
      m_pos_temp(),
      m_file_name(file_name)
{}

stem::Lexer::~Lexer()
{
  m_token_stream.clear();
  ss.clear();
}

void stem::Lexer::init(std::list<char> *char_list, int line_num)
{
  m_char_list = char_list;
  m_itr = m_char_list->begin();
  m_end = m_char_list->end();
  m_token_temp.init();
  m_pos_temp.init();
  m_pos_temp.m_file_name = m_file_name;
  m_pos_temp.m_line_num = line_num;
  m_pos_temp.m_column_nums[0] = 0;
  m_token_stream.clear();
  ss.str(std::string());
}

stem::TokenType stem::Lexer::charToTokenType(char &ch)
{
  stem::TokenType type = stem::TokenType::UNKNOWN;

  // if char exists in RT map
  if (stem::TokenUtils::m_RT_map.find(std::string(1, ch)) != stem::TokenUtils::m_RT_map.end())
  {
    type = stem::TokenUtils::m_RT_map[std::string(1, ch)];
  }

  return type;
}

void stem::Lexer::err(char &ch)
{
  m_pos_temp.m_column_nums[1] = m_pos_temp.m_column_nums[0];
  m_pos_temp.m_column_nums[0]--;
  stem::IllegalCharError err(m_pos_temp, "'" + std::string(1, ch) + "'");
  std::cout << err.to_string() << std::endl;
  exit(1);
}

void stem::Lexer::toTokenStream()
{
  if (stem::TokenUtils::m_RT_map.find(ss.str()) != stem::TokenUtils::m_RT_map.end())
      m_token_temp.m_type = TokenUtils::m_RT_map[ss.str()];
  m_token_temp.m_lexemes = ss.str();
  m_token_temp.m_pos.m_column_nums[1] = m_pos_temp.m_column_nums[0] - 1;
  m_token_stream.push_back(m_token_temp);

  m_token_temp.init();
  ss.str(std::string());
}

void stem::Lexer::createToken(stem::TokenType &type, char &ch)
{
  m_token_temp.m_type = type;
  m_token_temp.m_pos.m_line_num = m_pos_temp.m_line_num;
  m_token_temp.m_pos.m_column_nums[0] = m_pos_temp.m_column_nums[0];
  m_token_temp.m_pos.m_file_name = m_file_name;
  ss << ch;
}

void stem::Lexer::scanOneChar(char &ch)
{
  stem::TokenType type = charToTokenType(ch);

  // FIXME implement a more clean solution
  switch (type)
  {
  case TokenType::SPACE:
    switch (m_token_temp.m_type)
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
      m_token_temp.m_type = type;
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::SEMICOLON:
    switch (m_token_temp.m_type)
    {
    case TokenType::IDENTIFIER:
    case TokenType::DIGIT:
    case TokenType::RPAREN:
    case TokenType::RBRACE:
    case TokenType::RBRACKET:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::COLON:
    err(ch);
    break;
  case TokenType::LPAREN:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    case TokenType::IDENTIFIER:
    case TokenType::RBRACKET:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::RPAREN:
    switch (m_token_temp.m_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::LBRACKET:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::RBRACKET:
    switch (m_token_temp.m_type)
    {
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::LBRACE:
    switch (m_token_temp.m_type)
    {
    case TokenType::EMPTY:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::RBRACE:
    switch (m_token_temp.m_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::AMPERSAND:
    err(ch);
    break;
  case TokenType::VSLASH:
    switch(m_token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::TILDE:
    err(ch);
    break;
  case TokenType::EQUAL:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    case TokenType::IDENTIFIER:
    case TokenType::DIGIT:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::LESSTHAN:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
    case TokenType::DIGIT:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::MORETHAN:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
    case TokenType::DIGIT:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::EXCLAMATION:
    switch (m_token_temp.m_type)
    {
    case TokenType::DIGIT:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::COMMA:
    switch (m_token_temp.m_type)
    {
    case TokenType::DIGIT:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::DOT:
    switch (m_token_temp.m_type)
    {
    case TokenType::DIGIT:
      if (m_dot_count > 1)
      {
        stem::IllegalCharError err(m_pos_temp, "DIGIT already has DOT '.'");
        std::cout << err.to_string() << std::endl;
        exit(1);
      }
      else
      {
        ss << ch;
        ++m_dot_count;
      }
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::PLUS:
    switch (m_token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::MINUS:
    switch (m_token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::ASTERISK:
    switch (m_token_temp.m_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, ch);
      break;
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::FSLASH:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
    case TokenType::EMPTY:
      createToken(type, ch);
      break;
    case TokenType::FSLASH:
      ss << ch;
      if (TokenType::COMMENT == TokenUtils::m_RT_map[ss.str()])
      {
        m_token_temp.m_type = TokenType::COMMENT;
      }
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::PERCENT:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    case TokenType::IDENTIFIER:
    case TokenType::DIGIT:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::CARET:
    switch (m_token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::UNDERSCORE:
    switch (m_token_temp.m_type)
    {
    case TokenType::IDENTIFIER:
      toTokenStream();
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::DIGIT:
    switch (m_token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, ch);
      m_dot_count = 0;
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      ss << ch;
      break;
    case TokenType::LPAREN:
    case TokenType::ASTERISK:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::CARET:
    case TokenType::EQUAL:
      toTokenStream();
      createToken(type, ch);
      m_dot_count = 0;
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::IDENTIFIER:
    switch (m_token_temp.m_type)
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
      createToken(type, ch);
      break;
    case TokenType::SPACE:
    case TokenType::EMPTY:
      createToken(type, ch);
      break;
    case TokenType::IDENTIFIER:
      ss << ch;
      break;
    default:
      err(ch);
    }
    break;
  default:
    err(ch);
    break;
  }
}

bool stem::Lexer::lex(std::list<char> *char_list, int line_num)
{
  //* initialize variables
  init(char_list, line_num);
  //* check char list size
  if (m_char_list->size() == 0) return false;

  //* iterate through char list and convert to token stream
  while (m_itr != m_end)
  {
    ++m_pos_temp.m_column_nums[0];

    //std::cout << "char: " << *m_itr << " ";
    scanOneChar(*m_itr);
    //std::cout << "ss: " << ((ss.str().length() == 0) ? "(null)" : ss.str()) << std::endl;

    ++m_itr;
  }

  //* Add last remaining token to stream
  if (m_token_temp.m_type != TokenType::EMPTY)
  {
    if (m_token_temp.m_type != TokenType::COMMENT)
    {
      toTokenStream();
    }
    else 
    {
      m_token_temp.init();
      ss.str(std::string());
    }
  }
  return true;
}

std::list<stem::Token> *stem::Lexer::getList()
{
  return &m_token_stream;
}
