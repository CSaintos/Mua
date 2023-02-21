/**
 * @brief This file is part of {{ stem.inc.util.node }}
 * 
 * @file OpNode.hpp
 * @author Christian Santos
 * @version 1.0.0 02/20/2023
*/

#pragma once

#include "Node.hpp"
#include "Token.hpp"

namespace stem
{
  /**
   * @pure @struct OpNode
   * @brief Specifies generic operator node
   * - Used for Operators
   */
  struct OpNode : virtual public Node
  {
    /**
     * @brief virtual OpNode destructor
    */
    inline virtual ~OpNode(){};

    /**
     * @return false because an operator node is not a leaf
     * ? Is it though?
     */
    inline bool isLeaf() override { return false; }
  };
}