#include "DigitNode.hpp"

stem::DigitNode::DigitNode(Token &tok_digit)
{
  m_tok = tok_digit;
}

stem::DigitNode::~DigitNode()
{}

// std::string stem::DigitNode::to_string()
// {
//   return m_tok.to_string();
// }

// std::string stem::DigitNode::to_repr()
// {
//   return m_tok.m_lexemes;
// }