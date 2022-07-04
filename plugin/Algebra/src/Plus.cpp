#include "Plus.hpp"

std::unique_ptr<stem::EntryPoint> getObj(void)
{
  return std::make_unique<stem::math::Plus>();
}

std::string getName()
{
  return "Algebra:Plus, version:1.0.0";
}

void stem::math::Plus::entryPoint()
{
  std::cout << "Hello Plus" << std::endl;
}

stem::Node *stem::math::Plus::evaluate(stem::OpNode *op_node)
{
  if (op_node->m_tok_op.m_type != stem::TokenType::PLUS) return nullptr;
}