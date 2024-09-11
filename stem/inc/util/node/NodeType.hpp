/**
 * @file stem/inc/util/node/NodeType.hpp
 * @author Christian
 * @version 1.0.1 
 * @date 9/9/2024
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
    VALUE,
    BINARY_OPERATOR,
    UNARY_OPERATOR
  };
}
