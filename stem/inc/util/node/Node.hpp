/**
 * @file stem/inc/util/node/Node.hpp
 * @author Christian Santos
 * @version 1.1.0
 * @date 10/12/2024
 */

#pragma once

#include <iostream>
#include <memory>
#include <unordered_set>

#include "Token.hpp"
#include "NodeType.hpp"
#include "InterpretType.hpp"

namespace stem
{
  /**
   * @pure @struct Node
   * @brief Specifies generic node
   */
  struct Node
  {
    Node* parent = nullptr; ///< pointer to parent Node
    Token tok; ///< Default represented token

    virtual ~Node() = default;
    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    virtual std::string to_string() = 0;
    /**
     * @brief Returns combined lexemes of each token within each node
     * @note to representation
     * 
     * @return combined lexemes as a string
     */
    virtual std::string to_repr() = 0;
    /**
     * @return true if node is a leaf,
     * false otherwise.
     */
    virtual bool isLeaf() = 0;
    /**
     * @return true if node has grandchildren,
     * false otherwise.
     */
    virtual bool hasGrandchildren() = 0;
    /**
     * @return node type
     */
    virtual NodeType getType() = 0;
    /**
     * @return true if node is an exclusive parent,
     * false otherwise.
     * @note an exclusive parent is a parent node
     * that has no grandchildren.
     */
    bool isExclusiveParent();
    /**
     * @return true if a change was made, false otherwise
     * @note a change is represented by any modification of the parse_tree including modifications of any nodes by modifying their contents.
     * @note an exception: modification of Node.tok.pos is ignored at this stage until further notice.
     */
    virtual bool interpret(const std::unordered_set<InterpretType> &flags = {}) = 0;

    virtual std::unique_ptr<Node> copy() = 0;
  };
}
