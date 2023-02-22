/**
 * @brief This file is part {{ stem.inc.util.node.value_node }}
 * 
 * @file DigitNode.hpp
 * @author Christian Santos
 * @version 1.0.0 
 * @date 02/20/2023
*/

#pragma once

#include "ValueNode.hpp"
#include "Token.hpp"

namespace stem
{
  /**
   * @struct DigitNode
   * @brief node specifying digits
   */
  struct DigitNode final : virtual public ValueNode
  {
  public:
    /**
     * @brief DigitNode(tok) constructor
     */
    DigitNode(Token &tok_digit);
    /**
     * @brief ~DigitNode() destructor
     */
    ~DigitNode();

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
     * @return Digit node type
     */
    inline NodeType getType() override { return NodeType::DIGIT; }
  };
}