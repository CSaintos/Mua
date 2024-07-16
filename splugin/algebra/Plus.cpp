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
  //std::cout << "Why isn't this printing" << std::endl;
  if (op_node->m_tok.m_type != stem::TokenType::PLUS) return nullptr;
  
  if (op_node->getType() == NodeType::BINARY_OPERATOR)
  {
    stem::BinOpNode *bin_op_node = dynamic_cast<stem::BinOpNode*>(op_node);

    stem::Token *left_tok = &bin_op_node->m_node_left->m_tok;
    stem::Token *right_tok = &bin_op_node->m_node_right->m_tok;
    stem::Token *result_tok = &bin_op_node->m_tok;
    
    if (left_tok->m_type == stem::TokenType::DIGIT &&
        right_tok->m_type == stem::TokenType::DIGIT)
    {
      double left_num = std::stod(left_tok->m_lexemes);
      double right_num = std::stod(right_tok->m_lexemes);
      double result = left_num + right_num;

      result_tok->init();
      result_tok->m_lexemes = std::to_string(result);
      result_tok->m_type = stem::TokenType::DIGIT;

      std::cout << result << std::endl;
    }
  }

  return nullptr;
}