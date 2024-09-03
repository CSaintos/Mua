/**
 * @brief This file is part of {{ stem.inc.util.node }}
 * 
 * @file NodeType.hpp
 * @author Christian
 * @version 1.0.0 
 * @date 2/20/2023
*/

#pragma once

namespace stem
{
  /**
   * @enum NodeType
   * @brief Specifies Type of Node
   */
  enum class NodeType 
  {
    DIGIT,
    IDENTIFIER,
    VALUE,
    BINARY_OPERATOR,
    UNARY_OPERATOR
  };
}
