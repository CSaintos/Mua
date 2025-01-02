/**
 * @file stem/test/front/WriterTest.cpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 12/31/2024
 */

#include <iostream>

#include "Writer.hpp"

using namespace stem;
using namespace std;

int main(int argc, char *argv[])
{
  Writer writer(argv[argc - 1]);

  string text[5];

  text[0] = "Lorem ipsum dolor sit amet";
  text[1] = "consectetur adipiscing elit";
  text[2] = "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
  text[3] = "";
  text[4] = "Ut enim ad minim veniam";

  for (string str : text)
  {
    writer.writeLine(str);
  }
}
