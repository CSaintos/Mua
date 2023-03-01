/**
 * @brief This file is part of {{ stem.test.front }}
 * 
 * @file ReaderTest.cpp
 * @author Christian Santos
 * @version 1.0.0 5/15/2022
 */

#include <iostream>
#include <algorithm>

#include "Reader.hpp"

int main(int argc, char *argv[])
{
  // create reader with file name
  stem::Reader reader(argv[argc-1]);
  // print file name from reader
  std::cout << "Reader fileName: " << reader.getFileName() << std::endl;

  int line_length = 0;
  std::list<char> *the_list = nullptr;
  // Do ... while line_length isn't -1
  do 
  {
    // Read the next line and get the length
    line_length = reader.readLine();
    // Print the length of the line
    std::cout << "Line length: " << line_length << std::endl;
    // Get the character list from the reader as pointer.
    the_list = reader.getList();
    // for each element in char list
    //  print the elemnt
    std::for_each (
      the_list->begin(), // start
      the_list->end(), // end
      // lambda function to apply to each element
      [](const char n)
      {
        std::cout << "[" << n << "], ";
      }
    );
    std::cout << std::endl;

  } while (line_length != -1);
}
