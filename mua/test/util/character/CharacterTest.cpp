/**
 * @file mua/test/util/character/CharacterTest.cpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 8/5/2024
 */

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
