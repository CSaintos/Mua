/**
 * @brief This file is part of {{ stem.inc.back }}
 * 
 * @file Generator.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 7/2/2022
 */

#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "Node.hpp"
#include "EntryPoint.hpp"

namespace stem
{
  /**
   * @class Generator
   * 
   * @brief Handles evaluating parse tree and generating a result
   * @note still figuring out the details of how this is going to work. 
   */
  class Generator
  {
  public:
    /**
     * @brief Generator(&plugin_manager) constructor
     */
    Generator(std::vector<std::unique_ptr<stem::EntryPoint>> &entry_points);

    /**
     * @brief generates a result
     * 
     * @param root_node the root node of the parse tree
     */
    void generate(stem::Node *root_node);
  private:
    /// plugin vector used for evaluation
    std::vector<std::unique_ptr<stem::EntryPoint>> &m_entry_points;
    /// plugin vector iterator
    std::vector<std::unique_ptr<stem::EntryPoint>>::iterator m_itr;
    /// pointer to root node of parse tree
    stem::Node *m_root_node;
  };
}