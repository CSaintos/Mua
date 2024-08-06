/**
 * @file stem/inc/util/character/CharacterUtils.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 8/5/2024
 */

#pragma once

#include <unordered_map>
#include <string>

#include "CharacterType.hpp"

namespace stem
{
  /**
   * @brief Specifies maps to attributes of CharacterType
   */
  class CharacterUtils
  {
  private:
    CharacterUtils();
  public:
    /// char to CharacterType map
    static std::unordered_map<char, CharacterType> cC_map;
    /// CharacterType to repr (string) map
    static std::unordered_map<CharacterType, std::string> repr_map;
  };
}
