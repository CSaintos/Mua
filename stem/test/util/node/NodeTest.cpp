/**
 * @brief This file is part of {{ stem.test.util.node }}
 * 
 * @file NodeTest.cpp
 * @author Christian Santos
 * @version 1.0.2 9/11/2024
 */

#include <iostream>
#include <memory>

#include "Node.hpp"
#include "BinOpNode.hpp"
#include "ValueNode.hpp"
#include "Token.hpp"
#include "TokenType.hpp"

using namespace std;
using namespace stem;

int main(int argc, char *argv[])
{
  // Create tokens
  Token tok_0;
  tok_0.type = TokenType::DIGIT;
  tok_0.lexemes = "0";
  Token tok_1;
  tok_1.type = TokenType::DIGIT;
  tok_1.lexemes = "1";
  Token tok_plus;
  tok_plus.type = TokenType::PLUS;
  tok_plus.lexemes = "+";
  // Create nodes
  unique_ptr<Node> node_0 = std::make_unique<ValueNode>(tok_0);
  unique_ptr<Node> node_1 = std::make_unique<ValueNode>(tok_1);
  // std::unique_ptr<stem::Node> node_plus = std::make_unique<stem::BinOpNode>(tok_plus);
  // node_plus = std::make_unique<stem::BinOpNode>(node_0, node_plus, node_1);
  unique_ptr<Node> node_plus = std::make_unique<BinOpNode>(node_0, tok_plus, node_1);
  // Print single node
  cout << node_plus->to_string() << endl;

  return 0;
}
