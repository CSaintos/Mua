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
  if (curr != token_trie->getTrie())
  {
    if (curr->type != TokenType::EMPTY)
    {
      token_temp.type = curr->type;
    }
    curr = token_trie->getTrie();
  }

  if (token_temp.type == TokenType::DIGIT ||
  token_temp.type == TokenType::IDENTIFIER)
  {
    stringstream ss;
    for (list<Character>::const_iterator it = ls.begin(); it != ls.end(); ++it)
    {
      ss << it->c;
      if (ls.end() == std::next(it))
      {
        if (token_temp.pos.column_nums[0] != it->pos.column_nums[0])
        {
          token_temp.pos.column_nums[1] = it->pos.column_nums[0];
        }
      }
    }
    token_temp.lexemes = ss.str();
  //if (TokenUtils::m_RT_map.find(ss.str()) != TokenUtils::m_RT_map.end())
  //  token_temp.type = TokenUtils::m_RT_map[ss.str()];
  }
  
  if (token_temp.type == TokenType::COMMENT) return;
  token_stream.push_back(token_temp);

  token_temp.init();
  ls.clear();
}

void Lexer::createToken(const TokenType &type, Character &c)
{
  token_temp.type = type;
  token_temp.pos = c.pos;
  ls.push_back(c);
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
      if (token_temp.type == TokenType::COMMENT) break;
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
      if (token_temp.type == TokenType::COMMENT) break;
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
      if (curr->nodes.count(c.c) == 1)
      {
        curr = &(curr->nodes[c.c]);
      }
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
      break;
    default:
      toTokenStream();
      if (token_temp.type == TokenType::COMMENT) break;
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
        if (token_temp.type == TokenType::COMMENT) break;
        if (curr->nodes.count(c.c) == 1)
        {
          curr = (&curr->nodes[c.c]);
          createToken(curr->type, c);
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

    ++itr;
  }

  //* Add last remaining token to stream
  if (token_temp.type != TokenType::EMPTY)
  {
    if (token_temp.type != TokenType::COMMENT)
    {
      toTokenStream();
    }
    else 
    {
      token_temp.init();
      ls.clear();
    }
  }
  return true;
}

list<Token> *Lexer::getList()
{
  return &token_stream;
}
