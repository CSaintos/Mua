#include "Node.hpp"

bool stem::Node::isExclusiveParent()
{
  if (!isLeaf() && !hasGrandchildren())
  {
    return true;
  }
  return false;
}

stem::DigitNode::DigitNode(Token &tok_digit)
{
  m_tok_value = tok_digit;
  m_tok = &m_tok_value;
}

stem::DigitNode::~DigitNode()
{}

std::string stem::DigitNode::to_string()
{
  return m_tok_value.to_string();
}

std::string stem::DigitNode::to_repr()
{
  return m_tok_value.m_lexemes;
}

stem::IdentifierNode::IdentifierNode(Token &tok_identifier)
{
  m_tok_value = tok_identifier;
  m_tok = &m_tok_value;
}

stem::IdentifierNode::~IdentifierNode()
{}

std::string stem::IdentifierNode::to_string()
{
  return m_tok_value.to_string();
}

std::string stem::IdentifierNode::to_repr()
{
  return m_tok_value.m_lexemes;
}

stem::BinOpNode::BinOpNode(Token &tok_op)
{
  m_tok_op = tok_op;
  m_tok = &m_tok_op;
}

stem::BinOpNode::BinOpNode(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right)
    : m_node_left(std::move(node_left)), m_node_right(std::move(node_right))
{
  m_tok_op = Token(*node_op->m_tok);
  m_tok = &m_tok_op;
  node_op.release();
}

stem::BinOpNode::~BinOpNode()
{}

std::string stem::BinOpNode::to_string()
{
  if (m_node_left == nullptr || m_node_right == nullptr)
  {
    return ("(" + m_tok_op.to_string() + ")");
  }
  return ("(" + m_node_left->to_string() + ", "+ m_tok_op.to_string() + ", " + m_node_right->to_string() + ")");
}

std::string stem::BinOpNode::to_repr()
{
  if (m_node_left == nullptr || m_node_right == nullptr)
  {
    return m_tok_op.m_lexemes;
  }
  return m_node_left->to_repr() + m_tok_op.m_lexemes + m_node_right->to_repr();
}

bool stem::BinOpNode::hasGrandchildren()
{
  if (m_node_left->isLeaf() && m_node_right->isLeaf())
  {
    return false;
  }
  return true;
}

stem::UnaOpNode::UnaOpNode(Token &tok_op)
{
  m_tok_op = tok_op;
  m_tok = &m_tok_op;
}

stem::UnaOpNode::UnaOpNode(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node)
    : m_node(std::move(node))
{
  m_tok_op = Token(*(node_op->m_tok));
  m_tok = &m_tok_op;
  node_op.release();
}

stem::UnaOpNode::~UnaOpNode()
{}

std::string stem::UnaOpNode::to_string()
{
  return ("(" + m_node->to_string() + ", " + m_tok_op.to_string() + ")");
}

std::string stem::UnaOpNode::to_repr()
{
  std::string str = std::string();

  if (m_tok_op.m_type == stem::TokenType::LPAREN)
  {
    str = "(" + m_node->to_repr() + ")";
  }

  return str;
}

bool stem::UnaOpNode::hasGrandchildren()
{
  if (m_node->isLeaf())
  {
    return false;
  }
  return true;
}
