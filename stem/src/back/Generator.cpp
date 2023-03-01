#include "Generator.hpp"

stem::Generator::Generator(std::vector<std::unique_ptr<stem::EntryPoint>> &entry_points)
    : m_entry_points(entry_points)
{}

void stem::Generator::generate(stem::Node *root_node)
{
  m_root_node = root_node;

  // Let's assume you're iterating through the vector of exclusive parents
  // This is one instance of evaluating a single node
  if (m_root_node->isExclusiveParent())
  {
    for (m_itr = m_entry_points.begin(); m_itr != m_entry_points.end(); ++m_itr)
    {
      stem::OpNode *op_node = dynamic_cast<stem::OpNode*>(m_root_node);
      std::cout << m_root_node->to_repr() << std::endl;
      stem::Node *result = (*m_itr)->evaluate(op_node);
    }
  }
}