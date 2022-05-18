/**
 * @brief This file is part of {{ stem.test.util }}
 * 
 * @file NodeTest.cpp
 * @author Christian Santos
 * @version 1.0.0 5/17/2022
 */

#include <iostream>

#include "Node.hpp"
#include "Token.hpp"

int main(int argc, char *argv[])
{
  // Create tokens
  stem::Token tok_0;
  tok_0.m_type = stem::TokenType::DIGIT;
  tok_0.m_lexemes = "0";
  stem::Token tok_1;
  tok_1.m_type = stem::TokenType::DIGIT;
  tok_1.m_lexemes = "1";
  stem::Token tok_plus;
  tok_plus.m_type = stem::TokenType::PLUS;
  tok_plus.m_lexemes = "+";
  // Create nodes
  stem::DigitNode node_0(tok_0);
  stem::DigitNode node_1(tok_1);
  stem::BinOpNode node_plus(node_0, tok_plus, node_1);
  // Print single node
  std::cout << node_plus.to_string() << std::endl;

  return 0;
}