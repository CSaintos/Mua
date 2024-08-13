#include "UnaOpNode.hpp"

stem::UnaOpNode::UnaOpNode(Token &tok_op)
{
  m_tok = tok_op;
}

stem::UnaOpNode::UnaOpNode(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node)
    : m_node(std::move(node))
{
  m_tok = node_op->m_tok;
  node_op.release();
}

stem::UnaOpNode::UnaOpNode(Token &tok_op, std::unique_ptr<Node> &node)
  : m_node(std::move(node))
{
  m_tok = tok_op;
}

stem::UnaOpNode::~UnaOpNode()
{}

std::string stem::UnaOpNode::to_string()
{
  return ("(" + m_node->to_string() + ", " + m_tok.to_string() + ")");
}

std::string stem::UnaOpNode::to_repr()
{
  std::string str = std::string();

  if (m_tok.type == stem::TokenType::LPAREN)
  {
    str = "(" + m_node->to_repr() + ")";
  }

  return str;
}

bool stem::UnaOpNode::hasGrandchildren()
{
  return (!m_node->isLeaf());
}
