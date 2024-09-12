#include "UnaOpNode.hpp"

stem::UnaOpNode::UnaOpNode(Token &tok_op)
{
  tok = tok_op;
}

stem::UnaOpNode::UnaOpNode(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node)
    : node(std::move(node))
{
  tok = node_op->tok;
  void* trash = node_op.release();
  this->node->parent = this;
}

stem::UnaOpNode::UnaOpNode(Token &tok_op, std::unique_ptr<Node> &node)
  : node(std::move(node))
{
  tok = tok_op;
  this->node->parent = this;
}

stem::UnaOpNode::~UnaOpNode()
{}

std::string stem::UnaOpNode::to_string()
{
  return ("(" + tok.to_string() + ", " + node->to_string() + ")");
}

std::string stem::UnaOpNode::to_repr()
{
  std::string str = std::string();

  if (tok.type == stem::TokenType::LPAREN)
  {
    str = "(" + node->to_repr() + ")";
  }

  return str;
}

bool stem::UnaOpNode::hasGrandchildren()
{
  return (!node->isLeaf());
}
