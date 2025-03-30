/**
 * @file mua/inc/util/Number.hpp
 * @author Christian Santos
 * @version 1.0.0
 * #date 9/30/2024
 */
#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
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
#include "INodeFactory.hpp"

namespace mua
{
  class NumberUtils
  {
  private:
    NumberUtils();
    // Not OOP bc modifies parameter
    static void strToNumber(std::string number, std::list<Character> &whole_number, std::list<Character> &less_than_zero);
    static std::string listCharToStr(std::list<Character> &c_list);
    static int g(int x, int n, int b); // factorize helper function
  public:
    static std::string stripTrailingZeros(std::string number);
    static std::unique_ptr<Node> fractionalize(INodeFactory *node_factory, std::string number);
    static unsigned long long bpow(unsigned long long b, unsigned long long e);
    static unsigned long long mpow(unsigned long long b, unsigned long long e, unsigned long long m);
    static bool isPrime(int x);
    static std::list<int> factorize(const int n);
  };
}
