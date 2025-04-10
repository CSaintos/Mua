#include "UnaOpNode.hpp"

using namespace mua;
using namespace std;

UnaOpNode::UnaOpNode(INodeFactory *node_factory, Token &tok_op, unique_ptr<INodeState> state)
{
  this->node_factory = node_factory;
  tok = tok_op;
  this->state = std::move(state);
  this->state->setContext(this);
}

UnaOpNode::UnaOpNode(unique_ptr<Node> &node_op, unique_ptr<Node> &node)
  : node(std::move(node))
{
  tok = node_op->tok;
  void* trash = node_op.release();
  this->node->parent = this;
}

UnaOpNode::UnaOpNode(INodeFactory *node_factory, Token &tok_op, unique_ptr<Node> &node, unique_ptr<INodeState> state)
  : node(std::move(node))
{
  this->node_factory = node_factory;
  tok = tok_op;
  this->node->parent = this;
  this->state = std::move(state);
  this->state->setContext(this);
}

UnaOpNode::~UnaOpNode()
{}

string UnaOpNode::to_string()
{
  return ("(" + tok.to_string() + ", " + node->to_string() + ")");
}

bool UnaOpNode::hasGrandchildren()
{
  return (!node->isLeaf());
}

unique_ptr<Node> UnaOpNode::copy()
{
  //probably not safe code
  //return std::make_unique<Let>(tok, (unique_ptr<Node> &)*node->copy());
  unique_ptr<Node> node_copy = node->copy();
  return node_factory->produceNode(tok, node_copy);
}
