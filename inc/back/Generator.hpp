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

#include "Node.hpp"

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
     * @brief Generator() constructor
     */
    Generator();

    /**
     * @brief generates a result
     * 
     * @param root_node the root node of the parse tree
     */
    void generate(stem::Node *root_node);
  private:
    /// pointer to root node of parse tree
    stem::Node *m_root_node;
  };
}