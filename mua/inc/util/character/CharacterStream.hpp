/**
 * @file mua/inc/util/character/CharacterStream.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 1/2/2025
 */
#pragma once

#include <list>
#include <string>
#include <iostream>

#include "Character.hpp"
#include "Position.hpp"
#include "Error.hpp"

namespace mua
{
  /**
   * @brief Converts strings to list<Character>
   */
  class CharacterStream
  {
  private:
  public:
    Position pos;
    std::list<Character> strToCharacterList(std::string str); 
  };
}
