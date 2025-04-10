#include <iostream>

#include "TokenUtils.hpp"

using namespace mua;
using namespace std;

int main(int argc, char *argv[])
{
  cout << 
  TokenUtils::m_TS_map[TokenUtils::m_RT_map["+"]]
  << endl;
  
  return 0;
}
