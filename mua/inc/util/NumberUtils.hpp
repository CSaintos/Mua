#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <list>
#include <sstream>
#include <numeric>
#include <cmath>
#include <array>
#include <functional>

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
    
    static void strToNumber(std::string number, std::list<Character> &whole_number, std::list<Character> &less_than_one);
    static std::string listCharToStr(std::list<Character> &c_list);
    static int g(int x, int n, int b); // factorize helper function
    static double radicalFunction(double x, int e, int b);
    // TODO: improve performance of this algorithm
    static std::array<int, 2> findRadicalInterval(std::function<double(double)> f);
    static int toPrecision(double x);
    template<typename T> static int sign(T val);
    static double GTAB(std::function<double(double)> f, double x1, double x2, double eps); // Ganchovski-Traykov-Anderson-Bjork algorithm
  public:
    static std::string stripTrailingZeros(std::string number);
    static std::unique_ptr<Node> fractionalize(INodeFactory *node_factory, std::string number);
    static unsigned long long bpow(unsigned long long b, unsigned long long e);
    static unsigned long long mpow(unsigned long long b, unsigned long long e, unsigned long long m);
    static bool isPrime(int x);
    static std::list<int> factorize(const int n);
    static double findRadical(const int radicand, const int root);
  };
}
