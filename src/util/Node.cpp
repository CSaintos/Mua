#include "Node.hpp"

stem::DigitNode::DigitNode(Token tok)
{
  m_tok_value = tok;
}

stem::DigitNode::~DigitNode()
{}

std::string stem::DigitNode::to_string()
{
  return m_tok_value.to_string();
}

stem::IdentifierNode::IdentifierNode(Token tok)
{
  m_tok_value = tok;
}

stem::IdentifierNode::~IdentifierNode()
{}

std::string stem::IdentifierNode::to_string()
{
  return m_tok_value.to_string();
}

stem::BinOpNode::BinOpNode(std::unique_ptr<Node> &node_left, Token tok_op, std::unique_ptr<Node> &node_right)
    : m_node_left(std::move(node_left)), m_node_right(std::move(node_right))
{
  m_tok_op = tok_op;
}

stem::BinOpNode::~BinOpNode()
{}

std::string stem::BinOpNode::to_string()
{
  return (m_node_left->to_string() + ", "+ m_tok_op.to_string() + ", " + m_node_right->to_string());
}

stem::UnaOpNode::UnaOpNode(Token tok_op, std::unique_ptr<Node> &node)
    : m_node(std::move(node))
{
  m_tok_op = tok_op;
}

stem::UnaOpNode::~UnaOpNode()
{}

std::string stem::UnaOpNode::to_string()
{
  return (m_node->to_string() + ", " + m_tok_op.to_string());
}