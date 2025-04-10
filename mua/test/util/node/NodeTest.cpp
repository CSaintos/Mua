#include <iostream>
#include <memory>

#include "Node.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "ValueNode.hpp"
#include "node_state/Semicolon.hpp"
#include "node_state/Asterisk.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "INodeFactory.hpp"
#include "NodeFactory.hpp"

using namespace std;
using namespace mua;

// Something I learned about casting... you can't cast to pure virtual classes (classes that don't have their virtual functions and members defined.)
// For the future, casting is code smell (yes i know)
int main(int argc, char *argv[])
{
  unique_ptr<INodeFactory> node_factory = std::make_unique<NodeFactory>();
  // Create tokens
  Token digit;
  digit.type = TokenType::DIGIT;
  digit.lexemes = "0";
  unique_ptr<Node> node_digit = node_factory->produceNode(digit);
  Token semicolon;
  semicolon.type = TokenType::SEMICOLON;
  unique_ptr<Node> node_semi = node_factory->produceNode(semicolon, node_digit);

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
    unique_ptr<Node> node_a = node_factory->produceNode(a);
    unique_ptr<Node> node_b = node_factory->produceNode(b);
    temp_una->node = node_factory->produceNode(adj, node_a, node_b);
  }

  cout << temp->to_string() << endl;

  return 0;
}
