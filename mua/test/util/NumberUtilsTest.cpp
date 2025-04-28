#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

#include "NumberUtils.hpp"

using namespace std;
using namespace mua;

int main(int argc, char *argv[])
{
  std::map<int, list<int>> int_factors = 
  {
    {19, {}},
    {37, {}},
    {43, {}},
    {53, {}},
    {59, {}},
    {773, {}},
    {597529, {773, 773}},
    {14386849, {3793, 3793}},
    //{49547521, {7039, 7039}},
    {1974828707, {19, 43, 53, 59, 773}}
  };

  //int is_prime = atoi(argv[1]);
  //cout << "Is " << is_prime << " prime? " << (NumberUtils::isPrime(is_prime) ? "true" : "false") << endl;
  //exit(0);

  cout << "| key | match | assert | actual |" << endl;
  for (auto [key, claims] : int_factors)
  {
    std::list<int> actuals = NumberUtils::factorize(key);
    bool is_match = true;
    if (claims.size() == actuals.size())
    {
      std::list<int>::iterator ci = claims.begin();
      std::list<int>::iterator ai = actuals.begin();
      for (int i = 0; i < claims.size() && is_match; i++)
      {
        is_match = *ci == *ai;
      }
    }
    else
    {
      is_match = false;
    }
    std::stringstream claims_str; 
    std::stringstream actuals_str;
    std::list<int>::iterator end_check;
    for (std::list<int>::iterator itr = claims.begin(); itr != claims.end(); ++itr)
    {
      end_check = itr;
      end_check++;
      if (end_check == claims.end())
      {
        claims_str << std::to_string(*itr);
      }
      else
      {
        claims_str << std::to_string(*itr) << " ";
      }
    }
    for (std::list<int>::iterator itr = actuals.begin(); itr != actuals.end(); ++itr)
    {
      end_check = itr;
      end_check++;
      if (end_check == actuals.end())
      {
        actuals_str << std::to_string(*itr);
      }
      else
      {
        actuals_str << std::to_string(*itr) << " ";
      }
    }

    cout << "| " << key << " | " << is_match << " | " << claims_str.str() << " | " << actuals_str.str() << " |" << endl;
  }

  cout << endl;
  cout << "2^(1/2) = " << NumberUtils::findRadical(2, 2) << endl;

  return 0;
}
