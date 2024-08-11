#include "Lexer.hpp"

stem::Lexer::Lexer(const std::string &file_name)
    : char_list(),
      itr(),
      end(),
      pos_temp(),
      file_name(file_name)
{}

stem::Lexer::~Lexer()
{
  token_stream.clear();
  ss.clear();
}

void stem::Lexer::init(std::list<char> *char_list, int line_num)
{
  char_list = char_list;
  itr = char_list->begin();
  end = char_list->end();
  token_temp.init();
  pos_temp.init();
  pos_temp.file_name = file_name;
  pos_temp.line_num = line_num;
  pos_temp.column_nums[0] = 0;
  token_stream.clear();
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
  pos_temp.column_nums[1] = pos_temp.column_nums[0];
  pos_temp.column_nums[0]--;
  stem::IllegalCharError err(pos_temp, "'" + std::string(1, ch) + "'");
  std::cout << err.to_string() << std::endl;
  exit(1);
}

void stem::Lexer::toTokenStream()
{
  if (stem::TokenUtils::m_RT_map.find(ss.str()) != stem::TokenUtils::m_RT_map.end())
      token_temp.m_type = TokenUtils::m_RT_map[ss.str()];
  token_temp.m_lexemes = ss.str();
  token_temp.m_pos.column_nums[1] = pos_temp.column_nums[0] - 1;
  token_stream.push_back(token_temp);

  token_temp.init();
  ss.str(std::string());
}

void stem::Lexer::createToken(stem::TokenType &type, char &ch)
{
  token_temp.m_type = type;
  token_temp.m_pos.line_num = pos_temp.line_num;
  token_temp.m_pos.column_nums[0] = pos_temp.column_nums[0];
  token_temp.m_pos.file_name = file_name;
  ss << ch;
}

void stem::Lexer::scanOneChar(char &ch)
{
  stem::TokenType type = charToTokenType(ch);

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
      err(ch);
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
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, ch);
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
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::RPAREN:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
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
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::RBRACKET:
    switch (token_temp.m_type)
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
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, ch);
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::RBRACE:
    switch (token_temp.m_type)
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
    switch(token_temp.m_type)
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
    switch (token_temp.m_type)
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
    switch (token_temp.m_type)
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
    switch (token_temp.m_type)
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
    switch (token_temp.m_type)
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
    switch (token_temp.m_type)
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
    switch (token_temp.m_type)
    {
    case TokenType::DIGIT:
      if (dot_count > 1)
      {
        stem::IllegalCharError err(pos_temp, "DIGIT already has DOT '.'");
        std::cout << err.to_string() << std::endl;
        exit(1);
      }
      else
      {
        ss << ch;
        ++dot_count;
      }
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::PLUS:
  case TokenType::MINUS:
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, ch);
      break;
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
  case TokenType::ASTERISK:
  case TokenType::PERCENT:
  case TokenType::CARET:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
      createToken(type, ch);
      break;
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
  case TokenType::FSLASH:
    switch (token_temp.m_type)
    {
    case TokenType::SPACE:
    case TokenType::EMPTY:
      createToken(type, ch);
      break;
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
    case TokenType::RPAREN:
      toTokenStream();
      createToken(type, ch);
      break;
    case TokenType::FSLASH:
      ss << ch;
      if (TokenType::COMMENT == TokenUtils::m_RT_map[ss.str()])
      {
        token_temp.m_type = TokenType::COMMENT;
      }
      break;
    default:
      err(ch);
    }
    break;
  case TokenType::UNDERSCORE:
    switch (token_temp.m_type)
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
    switch (token_temp.m_type)
    {
    case TokenType::EMPTY:
    case TokenType::SPACE:
      createToken(type, ch);
      dot_count = 0;
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
      dot_count = 0;
      break;
    default:
      err(ch);
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
  if (char_list->size() == 0) return false;

  //* iterate through char list and convert to token stream
  while (itr != end)
  {
    ++pos_temp.column_nums[0];

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
      ss.str(std::string());
    }
  }
  return true;
}

std::list<stem::Token> *stem::Lexer::getList()
{
  return &token_stream;
}
