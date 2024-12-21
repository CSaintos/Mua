/**
 * @file stem/inc/util/Number.hpp
 * @author Christian Santos
 * @version 1.0.0
 * #date 9/30/2024
 */
#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <list>
#include <sstream>
#include <numeric>
#include <cmath>

#include "Character.hpp"
#include "CharacterType.hpp"
#include "CharacterUtils.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "FSlash.hpp"

namespace stem
{
  class NumberUtils
  {
  private:
    NumberUtils();
    // Not OOP bc modifies parameter
    static void strToNumber(std::string number, std::list<Character> &whole_number, std::list<Character> &less_than_zero);
    static std::string listCharToStr(std::list<Character> &c_list);
    static int g(int x, int n); // factorize helper function
    static bool isPrime(int x);
  public:
    static std::string stripTrailingZeros(std::string number);
    static std::unique_ptr<Node> fractionalize(std::string number);
    static std::list<int> factorize(const int n);
  };
}
