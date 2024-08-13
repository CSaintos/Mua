#include "BinOpNode.hpp"

stem::BinOpNode::BinOpNode(Token &tok_op)
{
  m_tok = tok_op;
}

stem::BinOpNode::BinOpNode(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right)
    : m_node_left(std::move(node_left)), m_node_right(std::move(node_right))
{
  m_tok = node_op->m_tok;
  node_op.release();
}

stem::BinOpNode::BinOpNode(std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right)
  : m_node_left(std::move(node_left)), m_node_right(std::move(node_right))
{
  m_tok = tok_op;
}

stem::BinOpNode::~BinOpNode()
{}

std::string stem::BinOpNode::to_string()
{
  if (m_node_left == nullptr || m_node_right == nullptr)
  {
    return ("(" + m_tok.to_string() + ")");
  }
  return ("(" + m_node_left->to_string() + ", " + m_tok.to_string() + ", " + m_node_right->to_string() + ")");
}

std::string stem::BinOpNode::to_repr()
{
  if (m_node_left == nullptr || m_node_right == nullptr)
  {
    return m_tok.lexemes;
  }
  return m_node_left->to_repr() + m_tok.lexemes + m_node_right->to_repr();
}

bool stem::BinOpNode::hasGrandchildren()
{
  return (!m_node_left->isLeaf() || !m_node_right->isLeaf());
}
