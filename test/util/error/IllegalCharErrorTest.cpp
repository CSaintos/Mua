/**
 * @brief This file is part of {{ stem.test.util }}
 * 
 * @file IllegalCharErrorTest.cpp
 * @author Christian Santos
 * @version 1.0.0 5/16/2022
 */

#include <string>
#include <iostream>

#include "Position.hpp"
#include "IllegalCharError.hpp"

int main(int argc, char *argv[])
{
  stem::Position pos = stem::Position("TestFile.txt", 0, 0);
  std::string details = "Sample Exception Details";
  stem::IllegalCharError err(pos, details);
  std::cout << err.to_string() << std::endl;

  return 0;
}