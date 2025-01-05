/**
 * @file mua/inc/util/node/ValueNode.hpp
 * @author Christian Santos
 * @version 1.0.2 
 * @date 10/12/2024
*/

#pragma once

#include <unordered_set>

#include "Token.hpp"
#include "Node.hpp"
#include "NodeType.hpp"
#include "InterpretType.hpp"

namespace mua
{
  /**
   * @struct ValueNode
   * @brief Specifies generic value node
   * - Used for Digits and Identifiers
   */
  struct ValueNode : public Node
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
      return tok.to_string();
    }
    /**
     * @brief Returns combined lexemes of each token within each node
     * @note to representation
     * 
     * @return combined lexemes as a string
     */
    inline std::string to_repr() override 
    {
      return tok.lexemes;
    }

    /**
     * @return Value node type
     */
    inline NodeType getType() override { return NodeType::VALUE; }

    inline bool interpret(const std::unordered_set<InterpretType> &flags = {}) override { return false; }

    std::unique_ptr<Node> copy() override;
  };
}
