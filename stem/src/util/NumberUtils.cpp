#include "NumberUtils.hpp"

using namespace std;
using namespace stem;

string NumberUtils::stripTrailingZeros(string number)
{
  list<Character> c_list;
  list<Character>::iterator itr_at_dot;
  list<Character>::iterator itr_at_end;
  for (char c : number)
  {
    CharacterType c_type = CharacterUtils::cC_map[c];
    if (c_type == CharacterType::DIGIT)
    {
      Character character;
      character.type = CharacterType::DIGIT;
      character.c = c;
      c_list.push_back(character);
    }
    else if (c_type == CharacterType::DOT)
    {
      Character character;
      character.type = CharacterType::DOT;
      character.c = c;
      c_list.push_back(character);
      itr_at_dot = c_list.end();
      itr_at_dot--;
    }
    else
    { 
      cout << "error" << endl;
    }
  }

  itr_at_end = c_list.end();
  bool loop = true;
  while (itr_at_end != itr_at_dot && loop)
  {
    itr_at_end--;
    if (itr_at_end->c == '0')
    {
      c_list.pop_back();
    }
    else
    {
      loop = false;
    }
  }

  if (itr_at_end == itr_at_dot)
  {
    itr_at_dot = list<Character>::iterator();
    itr_at_end = itr_at_dot;
    c_list.pop_back();
  }

    stringstream ss;
  
  for (auto c : c_list)
  {
    ss << c.c;
  }

  return ss.str();
}
