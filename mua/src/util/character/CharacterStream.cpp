#include "CharacterStream.hpp"

using namespace std;
using namespace mua;

list<Character> CharacterStream::strToCharacterList(string str)
{
  list<Character> character_list;
  for (char c : str)
  {
    pos.column_nums[0]++;
    Character character;
    character.c = c;
    character.pos = pos;
    if (CharacterUtils::cC_map.contains(c))
    {
      character.type = CharacterUtils::cC_map[c];
      character_list.push_back(Character(character));
    }
    else
    {
      character.type = CharacterType::UNKNOWN;
      Error err(pos, "IllegalCharError", character.to_string());
      cout << err.to_string() << endl;
    }
  }
  return character_list;
}
