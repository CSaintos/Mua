#include "BinOpNode.hpp"

using namespace std;
using namespace stem;

BinOpNode::BinOpNode(Token &tok_op)
{
  tok = tok_op;
}

BinOpNode::BinOpNode(unique_ptr<stem::Node> &node_left, unique_ptr<stem::Node> &node_op, unique_ptr<stem::Node> &node_right)
  : node_left(std::move(node_left)), node_right(std::move(node_right))
{
  tok = node_op->tok;
  void* trash = node_op.release();
  this->node_left->parent = this;
  this->node_right->parent = this;
}

BinOpNode::BinOpNode(unique_ptr<stem::Node> &node_left, Token &tok_op, unique_ptr<stem::Node> &node_right)
  : node_left(std::move(node_left)), node_right(std::move(node_right))
{
  tok = tok_op;
  this->node_left->parent = this;
  this->node_right->parent = this;
}

string BinOpNode::to_string()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return ("(" + tok.to_string() + ")");
  }
  if (tok.type == TokenType::ADJACENT)
  {
    return ("(" + node_left->to_string() + ", " + node_right->to_string() + ")");
  }
  return ("(" + node_left->to_string() + ", " + tok.to_string() + ", " + node_right->to_string() + ")");
}

string BinOpNode::to_repr()
{
  if (node_left == nullptr || node_right == nullptr)
  {
    return tok.lexemes;
  }
  return node_left->to_repr() + tok.lexemes + node_right->to_repr();
}

bool BinOpNode::hasGrandchildren()
{
  return (!node_left->isLeaf() || !node_right->isLeaf());
}

bool BinOpNode::interpret(const unordered_set<InterpretType> &flags)
{
  cout << "BinOpNode interpret" << endl;
  return false;
}
