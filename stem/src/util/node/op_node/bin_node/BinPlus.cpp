#include "BinPlus.hpp"

using namespace std;
using namespace stem;

BinPlus::BinPlus(Token &tok_op)
  : BinOpNode(tok_op) 
{}

BinPlus::BinPlus(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, node_op, node_right)
{}

BinPlus::BinPlus(unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : BinOpNode(node_left, tok_op, node_right)
{}

void BinPlus::interpret() 
{
  cout << "This ran" << endl;
  if (node_left->isLeaf() && node_right->isLeaf())
  {
    if (node_left->tok.type == TokenType::DIGIT &&
      node_right->tok.type == TokenType::DIGIT)
    {
      double lhs = std::stod(node_left->tok.lexemes);
      double rhs = std::stod(node_right->tok.lexemes);
      double result = lhs + rhs;

      Token res_tok;
      res_tok.lexemes = std::to_string(result);
      res_tok.type = TokenType::DIGIT;

      unique_ptr<ValueNode> res_node = std::make_unique<ValueNode>(res_tok);

      if (this->parent->getType() == NodeType::BINARY_OPERATOR)
      {
        BinOpNode* parent = static_cast<BinOpNode*>(this->parent);
        cout << "this is risque" << endl;
        if (parent->node_left.get() == this)
        {
          parent->node_left = std::move(res_node);
        }
        else if (parent->node_right.get() == this)
        {
          parent->node_right = std::move(res_node);
        }
        else 
        {
          cout << "Node pointers don't match" << endl;
        }
        cout << "It worked" << endl;
      }
      else if (this->parent->getType() == NodeType::UNARY_OPERATOR)
      {
        UnaOpNode* parent = static_cast<UnaOpNode*>(this->parent);
        cout << "this is risque" << endl;
        parent->node = std::move(res_node);
        cout << "It worked" << endl;
      }
    }
  }
}
