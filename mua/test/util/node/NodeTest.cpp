/**
 * @file mua/test/util/node/NodeTest.cpp
 * @author Christian Santos
 * @version 1.0.3 9/12/2024
 */

#include <iostream>
#include <memory>

#include "Node.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "ValueNode.hpp"
#include "Semicolon.hpp"
#include "Asterisk.hpp"
#include "Token.hpp"
#include "TokenType.hpp"

using namespace std;
using namespace mua;

// Something I learned about casting... you can't cast to pure virtual classes (classes that don't have their virtual functions and members defined.)
// For the future, casting is code smell (yes i know)
int main(int argc, char *argv[])
{
  // Create tokens
  Token digit;
  digit.type = TokenType::DIGIT;
  digit.lexemes = "0";
  unique_ptr<Node> node_digit = std::make_unique<ValueNode>(digit);
  Token semicolon;
  semicolon.type = TokenType::SEMICOLON;
  unique_ptr<Node> node_semi = std::make_unique<Semicolon>(semicolon, node_digit);

  Node* temp = node_semi.get();
  UnaOpNode* temp_una = static_cast<UnaOpNode*>(temp);
  cout << (temp == nullptr) << endl; // Yes this is necessary, make sure to check your pointers b4 using them, otherwise you get a no-error error.
  {
    Token a;
    a.type = TokenType::IDENTIFIER;
    a.lexemes = "a";
    Token b;
    b.type = TokenType::IDENTIFIER;
    b.lexemes = "b";
    Token adj;
    adj.type = TokenType::ADJACENT;
    unique_ptr<Node> node_a = std::make_unique<ValueNode>(a);
    unique_ptr<Node> node_b = std::make_unique<ValueNode>(b);
    temp_una->node = std::make_unique<Asterisk>(node_a, adj, node_b);
  }

  cout << temp->to_string() << endl;

  return 0;
}
