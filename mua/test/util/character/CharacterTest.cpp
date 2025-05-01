#include <iostream>
#include <string>

#include "CharacterUtils.hpp"

using namespace std;
using namespace mua;

int main(int argc, char *argv[])
{
  string testString = "~!@%^&*()-_+={}[]|;:,.<>/ a0";

  for (char c : testString)
  {
    cout << CharacterUtils::repr_map[CharacterUtils::cC_map[c]] << endl;
  }

  return 0;
}
