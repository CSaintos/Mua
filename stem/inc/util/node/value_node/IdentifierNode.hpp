/**
 * @brief This file is part of {{ stem.inc.util.node.value_node }}
 * 
 * @file IdentifierNode.hpp
 * @author Christian Santos
 * @version 1.0.0 
 * @date 02/20/2023
*/

#pragma once

#include "ValueNode.hpp"
#include "Token.hpp"
#include "NodeType.hpp"

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
     * @return Identifier Node Type
     */
    inline NodeType getType() override { return NodeType::IDENTIFIER; }
  };
}
