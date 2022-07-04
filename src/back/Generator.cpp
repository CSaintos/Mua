#include "Generator.hpp"

stem::Generator::Generator(std::vector<std::unique_ptr<stem::EntryPoint>> &entry_points)
    : m_entry_points(entry_points)
{}

void stem::Generator::generate(stem::Node *root_node)
{
  m_root_node = root_node;
  
  std::cout << "Is a leaf node: " << (m_root_node->is_leaf() ? "true" : "false") << std::endl;
  std::cout << "Has grandchildren: " << (m_root_node->has_grandchildren() ? "true" : "false") << std::endl;

  // Let's assume you're iterating through the vector of exclusive parents
  // This is one instance of evaluating a single node
  if (!m_root_node->is_leaf() && !m_root_node->has_grandchildren())
  {
    for (m_itr = m_entry_points.begin(); m_itr != m_entry_points.end(); ++m_itr)
    {
      (*m_itr)->entryPoint();
    }
  }
}