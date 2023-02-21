/**
 * @brief This file is part of {{ stem.test.util.node }}
 * 
 * @file NodeTest.cpp
 * @author Christian Santos
 * @version 1.0.1 02/20/2023
 */

#include <iostream>
#include <memory>

#include "Node.hpp"
#include "DigitNode.hpp"
#include "BinOpNode.hpp"
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
  std::unique_ptr<stem::Node> node_0 = std::make_unique<stem::DigitNode>(tok_0);
  std::unique_ptr<stem::Node> node_1 = std::make_unique<stem::DigitNode>(tok_1);
  // std::unique_ptr<stem::Node> node_plus = std::make_unique<stem::BinOpNode>(tok_plus);
  // node_plus = std::make_unique<stem::BinOpNode>(node_0, node_plus, node_1);
  std::unique_ptr<stem::Node> node_plus = std::make_unique<stem::BinOpNode>(node_0, tok_plus, node_1);
  // Print single node
  std::cout << node_plus->to_string() << std::endl;

  return 0;
}