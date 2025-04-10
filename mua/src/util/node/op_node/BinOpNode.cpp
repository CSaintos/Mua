#include "BinOpNode.hpp"

using namespace std;
using namespace mua;

BinOpNode::BinOpNode(INodeFactory *node_factory, Token &tok_op)
{
  this->node_factory = node_factory;
  tok = tok_op;
}

BinOpNode::BinOpNode(unique_ptr<Node> &node_left, unique_ptr<Node> &node_op, unique_ptr<Node> &node_right)
  : node_left(std::move(node_left)), node_right(std::move(node_right))
{
  tok = node_op->tok;
  void* trash = node_op.release();
  this->node_left->parent = this;
  this->node_right->parent = this;
}

BinOpNode::BinOpNode(INodeFactory *node_factory, unique_ptr<Node> &node_left, Token &tok_op, unique_ptr<Node> &node_right)
  : node_left(std::move(node_left)), node_right(std::move(node_right))
{
  this->node_factory = node_factory;
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

unique_ptr<Node> BinOpNode::copy()
{
  unique_ptr<Node> lhs_node = node_left->copy();
  unique_ptr<Node> rhs_node = node_right->copy();
  return node_factory->produceNode(tok, lhs_node, rhs_node);
}
