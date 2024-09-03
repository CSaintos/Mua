/**
 * @file stem/inc/util/node/ValueNode.hpp
 * @author Christian Santos
 * @version 1.0.1 
 * @date 9/1/2024
*/

#pragma once

#include "Node.hpp"
#include "Token.hpp"
#include "NodeType.hpp"

namespace stem
{
  /**
   * @struct ValueNode
   * @brief Specifies generic value node
   * - Used for Digits and Identifiers
   */
  struct ValueNode : virtual public Node
  {
    ValueNode(Token &tok_value);

    /**
     * @return true because a value node is a leaf
     */
    inline bool isLeaf() override { return true; }

    /**
     * @return false because value node has no grandchildren
     */
    inline bool hasGrandchildren() override { return false; }

    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    inline std::string to_string() override 
    {
      return m_tok.to_string();
    }
    /**
     * @brief Returns combined lexemes of each token within each node
     * @note to representation
     * 
     * @return combined lexemes as a string
     */
    inline std::string to_repr() override 
    {
      return m_tok.lexemes;
    }

    /**
     * @return Value node type
     */
    inline NodeType getType() override { return NodeType::VALUE; }
  };
}
