/**
 * @brief This file is part of {{ stem.test.util }}
 * 
 * @file TokenTest.cpp
 * @author Christian Santos
 * @version 1.0.0 5/16/2022
 */

#include <iostream>

#include "TokenUtils.hpp"

int main(int argc, char *argv[])
{
  std::cout << 
  stem::TokenUtils::m_TS_map[stem::TokenUtils::m_RT_map["+"]]
  << std::endl;
  
  return 0;
}