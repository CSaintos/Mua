#include "IdentifierNode.hpp"

stem::IdentifierNode::IdentifierNode(Token &tok_identifier)
  : ValueNode(tok_identifier)
{}

stem::IdentifierNode::~IdentifierNode()
{}

// std::string stem::IdentifierNode::to_string()
// {
//   return m_tok.to_string();
// }

// std::string stem::IdentifierNode::to_repr()
// {
//   return m_tok.m_lexemes;
// }
