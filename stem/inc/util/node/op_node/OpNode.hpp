/**
 * @file stem/inc/util/node/OpNode.hpp
 * @author Christian Santos
 * @version 1.0.1 
 * @date 9/12/2024
*/

#pragma once

#include "Node.hpp"

namespace stem
{
  /**
   * @pure @struct OpNode
   * @brief Specifies generic operator node
   * - Used for Operators
   */
  struct OpNode : public Node
  {
    /**
     * @return false because an operator node is not a leaf
     * ? Is it though?
     */
    inline bool isLeaf() override { return false; }
  };
}
