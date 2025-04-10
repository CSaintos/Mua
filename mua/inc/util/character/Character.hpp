#pragma once

#include "CharacterType.hpp"
#include "CharacterUtils.hpp"
#include "Position.hpp"

namespace mua
{
  struct Character
  {
    CharacterType type;
    Position pos;
    char c;

    Character();
    /// copy constructor
    Character(const Character &character);
    void init();
    std::string to_string() const;
  };
}
