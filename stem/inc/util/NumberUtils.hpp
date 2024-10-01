/**
 * @file stem/inc/util/Number.hpp
 * @author Christian Santos
 * @version 1.0.0
 * #date 9/30/2024
 */
#pragma once

#include <string>
#include <iostream>
#include <list>
#include <sstream>

#include "Character.hpp"
#include "CharacterType.hpp"
#include "CharacterUtils.hpp"

namespace stem
{
  class NumberUtils
  {
  private:
    NumberUtils();
  public:
    static std::string stripTrailingZeros(std::string number);
  };
}
