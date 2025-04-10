#include <string>
#include <iostream>

#include "Position.hpp"
#include "Error.hpp"

using namespace std;
using namespace mua;

int main(int argc, char *argv[])
{
  Position pos = Position("TestFile.txt", 0, 0);
  string details = "Sample Exception Details";
  Error err(pos, "Sample error name", details);
  cout << err.to_string() << endl;

  return 0;
}
