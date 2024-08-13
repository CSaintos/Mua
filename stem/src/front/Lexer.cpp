#include "Lexer.hpp"

using namespace std;
using namespace stem;

Lexer::Lexer()
  : char_list(),
    itr(),
    end(),
    token_trie(nullptr),
    curr(nullptr),
    dot_count(0)
{
  token_trie = TokenTrie::getInstance();
}

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
  curr = token_trie->getTrie();
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
  //if (TokenUtils::m_RT_map.find(ss.str()) != TokenUtils::m_RT_map.end())
  //  token_temp.type = TokenUtils::m_RT_map[ss.str()];
  if (curr != token_trie->getTrie())
  {
    if (curr->type != TokenType::EMPTY)
    {
      token_temp.type = curr->type;
    }
    curr = token_trie->getTrie();
  }
  //token_temp.lexemes = ss.str();
  if (token_temp.type == TokenType::DIGIT ||
  token_temp.type == TokenType::IDENTIFIER)
  {
    stringstream ss;
    for (list<Character>::const_iterator it = ls.begin(); it != ls.end(); ++it)
    {
      ss << it->c;
      if (ls.end() == std::next(it))
      {
        token_temp.pos.column_nums[1] = it->pos.column_nums[1];
      }
    }
    token_temp.lexemes = ss.str();
  }
  token_stream.push_back(token_temp);

  token_temp.init();
  ls.clear();
  //ss.str(string());
}

void Lexer::createToken(const TokenType &type, Character &c)
{
  token_temp.type = type;
  token_temp.pos = c.pos;
  ls.push_back(c);
  //ss << c.c;
}

void Lexer::scanOneChar_bak(Character &c)
{
  TokenType type = charToTokenType(c.c);

  // FIXME implement a more clean solution
  switch (type)
  {
//  case TokenType::SPACE:
//    switch (token_temp.m_type)
//    {
//    case TokenType::DIGIT:
//    case TokenType::IDENTIFIER:
//    case TokenType::PLUS:
//    case TokenType::MINUS:
//    case TokenType::ASTERISK:
//    case TokenType::FSLASH:
//    case TokenType::PERCENT:
//    case TokenType::CARET:
//    case TokenType::RPAREN:
//    case TokenType::EQUAL:
//    case TokenType::EXCLAMATION:
//    case TokenType::LESSTHAN:
//    case TokenType::MORETHAN:
//    case TokenType::COMMA:
//    case TokenType::VSLASH:
//      toTokenStream();
//      token_temp.m_type = type;
//      break;
//    case TokenType::SPACE:
//      break;
//    default:
//      err(c);
//    }
//    break;
  case TokenType::SEMICOLON:
    switch (token_temp.type)
    {
    case TokenType::IDENTIFIER:
    case TokenType::DIGIT:
    case TokenType::RPAREN:
//    case TokenType::RBRACE:
//    case TokenType::RBRACKET:
      toTokenStream();
      createToken(type, c);
      break;
    default:
      err(c);
    }
    break;
//  case TokenType::COLON:
//    err(c);
//    break;
  case TokenType::LPAREN:
    switch (token_temp.type)
    {
    case TokenType::EMPTY:
//    case TokenType::SPACE:
      createToken(type, c);
      break;
    case TokenType::IDENTIFIER:
    case TokenType::LPAREN:
//    case TokenType::RBRACKET:
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
    switch (token_temp.type)
    {
//    case TokenType::SPACE:
//      createToken(type, c);
//      break;
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
//  case TokenType::LBRACKET:
//    switch (token_temp.m_type)
//    {
//    case TokenType::SPACE:
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::RBRACKET:
//    switch (token_temp.m_type)
//    {
//    case TokenType::IDENTIFIER:
//      toTokenStream();
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::LBRACE:
//    switch (token_temp.m_type)
//    {
//    case TokenType::EMPTY:
//    case TokenType::SPACE:
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::RBRACE:
//    switch (token_temp.m_type)
//    {
//    case TokenType::DIGIT:
//    case TokenType::IDENTIFIER:
//      toTokenStream();
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::AMPERSAND:
//    err(c);
//    break;
//  case TokenType::VSLASH:
//    switch(token_temp.m_type)
//    {
//    case TokenType::SPACE:
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::TILDE:
//    err(c);
//    break;
  case TokenType::EQUAL:
    switch (token_temp.type)
    {
//    case TokenType::SPACE:
//      createToken(type, c);
//      break;
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
//  case TokenType::LESSTHAN:
//    switch (token_temp.m_type)
//    {
//    case TokenType::SPACE:
//    case TokenType::DIGIT:
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::MORETHAN:
//    switch (token_temp.m_type)
//    {
//    case TokenType::SPACE:
//    case TokenType::DIGIT:
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::EXCLAMATION:
//    switch (token_temp.m_type)
//    {
//    case TokenType::DIGIT:
//      toTokenStream();
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::COMMA:
//    switch (token_temp.m_type)
//    {
//    case TokenType::DIGIT:
//      toTokenStream();
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
//  case TokenType::DOT:
//    switch (token_temp.m_type)
//    {
//    case TokenType::DIGIT:
//      if (dot_count > 1)
//      {
//        Error err(c.pos, "IllegalCharError", "DIGIT already has DOT '.'");
//        cout << err.to_string() << endl;
//        exit(1);
//      }
//      else
//      {
//        ss << c.c;
//        ++dot_count;
//      }
//      break;
//    default:
//      err(c);
//    }
//    break;
  case TokenType::PLUS:
  case TokenType::MINUS:
    switch (token_temp.type)
    {
    case TokenType::EMPTY:
//    case TokenType::SPACE:
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
    switch (token_temp.type)
    {
//    case TokenType::SPACE:
//      createToken(type, c);
//      break;
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
    switch (token_temp.type)
    {
//    case TokenType::SPACE:
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
        token_temp.type = TokenType::COMMENT;
      }
      break;
    default:
      err(c);
    }
    break;
//  case TokenType::UNDERSCORE:
//    switch (token_temp.m_type)
//    {
//    case TokenType::IDENTIFIER:
//      toTokenStream();
//      createToken(type, c);
//      break;
//    default:
//      err(c);
//    }
//    break;
  case TokenType::DIGIT:
    switch (token_temp.type)
    {
    case TokenType::EMPTY:
//    case TokenType::SPACE:
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
    switch (token_temp.type)
    {
    case TokenType::PERCENT:
    case TokenType::FSLASH:
    case TokenType::ASTERISK:
    case TokenType::PLUS:
    case TokenType::MINUS:
    case TokenType::CARET:
//    case TokenType::UNDERSCORE:
    case TokenType::LPAREN:
//    case TokenType::LBRACE:
//    case TokenType::LBRACKET:
    case TokenType::EQUAL:
      toTokenStream();
      createToken(type, c);
      break;
//    case TokenType::SPACE:
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

void Lexer::scanOneChar(Character &c)
{
  CharacterType type = c.type;
  
  switch (type)
  {
  case CharacterType::SPACE:
    switch (token_temp.type)
    {
    case TokenType::EMPTY:
    case TokenType::COMMENT:
    case TokenType::UNKNOWN:
      break;
    case TokenType::DIGIT:
      if (dot_count == 1)
      {
        Error err(c.pos, "IllegalCharError", "DIGIT cannot end with DOT '.'");
        cout << err.to_string() << endl;
        ls.pop_back();
        dot_count = 0;
      }
      if (ls.size() != 0)
      {
        toTokenStream();
      }
      break;
    default:
      toTokenStream();
      break;
    }
    break;
  case CharacterType::DOT:
    switch (token_temp.type)
    {
    case TokenType::DIGIT:
      if (dot_count > 0)
      {
        Error err(c.pos, "IllegalCharError", "DIGIT already has DOT '.'");
        cout << err.to_string() << endl;
      }
      else
      {
        ls.push_back(c);
        ++dot_count;
      }
      break;
    case TokenType::UNKNOWN:
    case TokenType::COMMENT:
      break;
    case TokenType::EMPTY:
      createToken(TokenType::DIGIT, c);
      ++dot_count;
    default:
      toTokenStream();
      createToken(TokenType::DIGIT, c);
      ++dot_count;
    }
    break;
  case CharacterType::DIGIT:
    switch (token_temp.type)
    {
    case TokenType::DIGIT:
      if (dot_count == 1)
      {
        ++dot_count;
      }
      // no break
    case TokenType::IDENTIFIER:
      ls.push_back(c);
      break;
    case TokenType::EMPTY:
      createToken(TokenType::DIGIT, c);
      dot_count = 0;
      break;
    case TokenType::COMMENT:
    case TokenType::UNKNOWN:
      break;
    default:
      toTokenStream();
      createToken(TokenType::DIGIT, c);
      dot_count = 0;
      break;
    }
    break;
  case CharacterType::ALPHA:
    switch (token_temp.type)
    {
    case TokenType::EMPTY:
      createToken(TokenType::IDENTIFIER, c);
      break;
    case TokenType::IDENTIFIER:
      if (curr->nodes.count(c.c) == 1)
      {
        curr = &(curr->nodes[c.c]);
      }
      else if (curr != token_trie->getTrie()) 
      {
        curr = token_trie->getTrie();
      }
      ls.push_back(c);
      break;
    case TokenType::COMMENT:
    case TokenType::UNKNOWN:
      break;
    case TokenType::DIGIT:
      if (dot_count == 1)
      {
        Error err(c.pos, "IllegalCharError", "DIGIT cannot end with DOT '.'");
        cout << err.to_string() << endl;
        ls.pop_back();
        dot_count = 0;
      }
      if (ls.size() != 0)
      {
        toTokenStream();
      }
      createToken(TokenType::IDENTIFIER, c);
      if (curr->nodes.count(c.c) == 1)
      {
        curr = &(curr->nodes[c.c]);
      }
    default:
      toTokenStream();
      createToken(TokenType::IDENTIFIER, c);
      if (curr->nodes.count(c.c) == 1)
      {
        curr = &(curr->nodes[c.c]);
      }
      break;
    }
  case CharacterType::UNKNOWN:
  case CharacterType::EMPTY:
    break;
  default:
    if (curr->nodes.count(c.c) == 1)
    {
      if (curr == token_trie->getTrie())
      {
        switch (token_temp.type)
        {
        case TokenType::DIGIT:
          if (dot_count == 1)
          {
            Error err(c.pos, "IllegalCharError", "DIGIT cannot end with DOT '.'");
            cout << err.to_string() << endl;
            ls.pop_back();
            dot_count = 0;
          }
          if (ls.size() != 0)
          {
            toTokenStream();
          }
          break;
        case TokenType::EMPTY:
        case TokenType::COMMENT:
        case TokenType::UNKNOWN:
          break;
        default:
          toTokenStream();
          break;
        }

        switch (token_temp.type)
        {
        case TokenType::COMMENT:
          break;
        default:
          createToken(curr->nodes[c.c].type, c);  
          break;
        }
      }
      else
      {
        ls.push_back(c);
      }
      curr = (&curr->nodes[c.c]);
    }
    else
    {
      if (curr != token_trie->getTrie())
      {
        toTokenStream();
        if (curr->nodes.count(c.c) == 1)
        {
          curr = (&curr->nodes[c.c]);
          createToken(curr->nodes[c.c].type, c);
        }
      }
    }
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
  if (token_temp.type != TokenType::EMPTY /*&&
      token_temp.m_type != TokenType::SPACE*/)
  {
    if (token_temp.type != TokenType::COMMENT)
    {
      toTokenStream();
    }
    else 
    {
      token_temp.init();
      ls.clear();
      //ss.str(string());
    }
  }
  return true;
}

list<Token> *Lexer::getList()
{
  return &token_stream;
}
