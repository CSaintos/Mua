/**
 * @brief This file is part of {{ stem.inc.util }}
 * 
 * @file node.hpp
 * @author Christian Santos
 * @version 1.0.0 5/17/2022
 */

#pragma once

#include "Token.hpp"

namespace stem
{
  /**
   * @pure @struct Node
   * @brief Specifies generic node
   */
  struct Node
  {
    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    virtual std::string to_string() = 0;
  };

  /**
   * @pure @struct ValueNode
   * @brief Specifies generic value node
   * - Used for Digits and Identifiers
   */
  struct ValueNode : virtual public Node
  {
    Token m_tok_value; ///< token value
  };

  /**
   * @pure @struct OpNode
   * @brief Specifies generic operator node
   * - Used for Operators
   */
  struct OpNode : virtual public Node
  {
    Token m_tok_op; ///< token operator
  };

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
    DigitNode(Token tok);
    /**
     * @brief ~DigitNode() destructor
     */
    ~DigitNode();

    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    std::string to_string() override;
  };

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
    IdentifierNode(Token tok);
    /**
     * @brief ~IdentifierNode() destructor
     */
    ~IdentifierNode();

    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    std::string to_string() override;
  };

  /**
   * @struct BinOpNode
   * @brief node specifying binary operators
   */
  struct BinOpNode final : virtual public OpNode
  {
  public:
    Node &m_node_left; ///< left operand
    Node &m_node_right; ///< right operand
    
    /**
     * @brief BinOpNode(node_left, tok_op, node_right) constructor
     */
    BinOpNode(ValueNode &node_left, Token tok_op, ValueNode &node_right);
    /**
     * @brief ~BinOpNode() destructor
     */
    ~BinOpNode();

    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    std::string to_string() override;
  };

  /**
   * @struct UnaOpNode
   * @brief node specifying unary operators
   */
  struct UnaOpNode final : virtual public OpNode
  {
    Node &m_node; ///< left operand

    /**
     * @brief UnaOpNode(tok_op, node)
     */
    UnaOpNode(Token tok_op, ValueNode &node);
    /**
     * @brief ~UnaOpNode() destructor
     */
    ~UnaOpNode();

    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    std::string to_string() override;
  };
}