/**
 * @brief This file is part of {{ stem.inc.util.node.value_node }}
 * 
 * @file IdentifierNode.hpp
 * @author Christian Santos
 * @version 1.0.0 02/20/2023
*/

#pragma once

#include "ValueNode.hpp"
#include "Token.hpp"

namespace stem
{
  /**
   * @struct IdentifierNode
   * @brief node specifying identifiers
   */
  struct IdentifierNode final : virtual public ValueNode
  {
  public:
    /**
     * @brief IdentifierNode(tok) constructor
     */
    IdentifierNode(Token &tok_identifier);
    /**
     * @brief ~IdentifierNode() destructor
     */
    ~IdentifierNode();

    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    // std::string to_string() override;

    /**
     * @brief Returns combined lexemes of each token within each node
     * 
     * @return combined lexemes as a string
     */
    // std::string to_repr() override;

    /**
     * @return Identifier Node Type
     */
    inline NodeType getType() override { return NodeType::IDENTIFIER; }
  };
}