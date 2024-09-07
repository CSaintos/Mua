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
#include "BinOpNode.hpp"
#include "ValueNode.hpp"
#include "Token.hpp"

int main(int argc, char *argv[])
{
  // Create tokens
  stem::Token tok_0;
  tok_0.type = stem::TokenType::DIGIT;
  tok_0.lexemes = "0";
  stem::Token tok_1;
  tok_1.type = stem::TokenType::DIGIT;
  tok_1.lexemes = "1";
  stem::Token tok_plus;
  tok_plus.type = stem::TokenType::PLUS;
  tok_plus.lexemes = "+";
  // Create nodes
  std::unique_ptr<stem::Node> node_0 = std::make_unique<stem::ValueNode>(tok_0);
  std::unique_ptr<stem::Node> node_1 = std::make_unique<stem::ValueNode>(tok_1);
  // std::unique_ptr<stem::Node> node_plus = std::make_unique<stem::BinOpNode>(tok_plus);
  // node_plus = std::make_unique<stem::BinOpNode>(node_0, node_plus, node_1);
  std::unique_ptr<stem::Node> node_plus = std::make_unique<stem::BinOpNode>(node_0, tok_plus, node_1);
  // Print single node
  std::cout << node_plus->to_string() << std::endl;

  return 0;
}
