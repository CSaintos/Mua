/**
 * @file mua/test/front/ReaderTest.cpp
 * @author Christian Santos
 * @version 1.0.1
 * @date 8/8/2024
 */

#include <iostream>
#include <algorithm>

#include "Reader.hpp"
#include "Character.hpp"

using namespace mua;
using namespace std;

int main(int argc, char *argv[])
{
  // create reader with file name
  Reader reader(argv[argc-1]);
  // print file name from reader
  //cout << "Reader fileName: " << reader.getFileName() << endl;

  int line_length = 0;
  list<Character> *the_list = nullptr;
  // Do ... while line_length isn't -1
  do 
  {
    // Read the next line and get the length
    line_length = reader.readLine();
    // Print the length of the line
    cout << "Line length: " << line_length << endl;
    // Get the character list from the reader as pointer.
    the_list = reader.getList();
    // for each element in char list
    //  print the elemnt
    std::for_each (
      the_list->begin(), // start
      the_list->end(), // end
      // lambda function to apply to each element
      [](const Character c)
      {
        cout << c.to_string() << " ";
      }
    );
    cout << endl;

  } while (line_length != -1);
}
