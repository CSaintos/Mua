#include "BinOpNode.hpp"

using namespace std;
using namespace stem;

BinOpNode::BinOpNode(Token &tok_op)
{
  m_tok = tok_op;
}

BinOpNode::BinOpNode(unique_ptr<stem::Node> &node_left, unique_ptr<stem::Node> &node_op, unique_ptr<stem::Node> &node_right)
  : m_node_left(std::move(node_left)), m_node_right(std::move(node_right))
{
  m_tok = node_op->m_tok;
  void* trash = node_op.release();
}

BinOpNode::BinOpNode(unique_ptr<stem::Node> &node_left, Token &tok_op, unique_ptr<stem::Node> &node_right)
  : m_node_left(std::move(node_left)), m_node_right(std::move(node_right))
{
  m_tok = tok_op;
}

string BinOpNode::to_string()
{
  if (m_node_left == nullptr || m_node_right == nullptr)
  {
    return ("(" + m_tok.to_string() + ")");
  }
  if (m_tok.type == TokenType::ADJACENT)
  {
    return ("(" + m_node_left->to_string() + ", " + m_node_right->to_string() + ")");
  }
  return ("(" + m_node_left->to_string() + ", " + m_tok.to_string() + ", " + m_node_right->to_string() + ")");
}

string BinOpNode::to_repr()
{
  if (m_node_left == nullptr || m_node_right == nullptr)
  {
    return m_tok.lexemes;
  }
  return m_node_left->to_repr() + m_tok.lexemes + m_node_right->to_repr();
}

bool BinOpNode::hasGrandchildren()
{
  return (!m_node_left->isLeaf() || !m_node_right->isLeaf());
}
