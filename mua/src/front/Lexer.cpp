#include "Lexer.hpp"

using namespace std;
using namespace mua;

Lexer::Lexer()
  : char_list(nullptr),
    itr(),
    end(),
    token_trie(nullptr),
    curr(nullptr),
    dot_count(0)
{
  token_trie = TokenTrie::getInstance();
}

void Lexer::init(list<Character> *char_list)
{
  char_list = char_list;
  itr = char_list->begin();
  end = char_list->end();
  token_temp.init();
  token_stream.clear();
  ls.clear();
  curr = token_trie->getTrie();
}

void Lexer::toTokenStream()
{
  if (curr != token_trie->getTrie())
  {
    if (curr != nullptr && curr->type != TokenType::EMPTY)
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
      break;
    default:
      toTokenStream();
      break;
    }
    break;
  case CharacterType::UNKNOWN:
  case CharacterType::EMPTY:
    break;
  default:
    if (curr != nullptr && curr->nodes.count(c.c) == 1)
    {
      if (curr == token_trie->getTrie())
      {
        if (token_temp.type != TokenType::COMMENT)
        {
          createToken(curr->nodes[c.c]->type, c);
          if (token_temp.type == TokenType::DIGIT)
          {
            dot_count = 0;
          }
        }
      }
      else
      {
        ls.push_back(c);
      }
      curr = curr->nodes[c.c].get();
    }
    else
    {
      if (curr == token_trie->getTrie()) break;
      TokenType token_type = token_trie->getTrie()->nodes[c.c]->type;
      if (token_temp.type == TokenType::IDENTIFIER || token_temp.type == TokenType::DIGIT)
      {
        if (token_type == token_temp.type)
        {
          if (c.type == CharacterType::DOT)
          {
            if (dot_count > 0)
            {
              Error err(c.pos, "IllegalCharError", "DIGIT already has DOT '.'");
              cout << err.to_string() << endl;
              break;             
            }
            ++dot_count;
          }
          else if (dot_count == 1)
          {
            ++dot_count;
          }
          ls.push_back(c);
          if (curr != nullptr) curr = nullptr;
        }
        else
        {
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
          if (curr != nullptr && curr->nodes.count(c.c) == 1)
          {
            curr = curr->nodes[c.c].get();
            createToken(curr->type, c);
            if (token_temp.type == TokenType::DIGIT)
            {
              cout << "When is this true. Output in lexer btw" << endl;
              dot_count = 0;
              if (c.type == CharacterType::DOT)
              {
                ++dot_count;
              }
            }
            else if (dot_count != 0)
            {
              dot_count = 0;
            }
          }
        }
      }
      else 
      {
        switch (token_temp.type)
        {
        case TokenType::COMMENT:
        case TokenType::UNKNOWN:
          break;
        default:
          toTokenStream();
          if (token_temp.type == TokenType::COMMENT) break;
          if (curr->nodes.count(c.c) == 1)
          {
            curr = curr->nodes[c.c].get();
            createToken(curr->type, c);
          }
          break;
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
    //cout << "char: " << itr->c << " " << endl;
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
  }
  return true;
}

list<Token> *Lexer::getList()
{
  return &token_stream;
}
