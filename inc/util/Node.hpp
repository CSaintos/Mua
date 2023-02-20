/**
 * @brief This file is part of {{ stem.inc.util }}
 * 
 * @file node.hpp
 * @author Christian Santos
 * @version 1.0.5 7/5/2022
 */

#pragma once

#include <iostream>
#include <memory>

#include "Token.hpp"

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
    BINARY_OPERATOR,
    UNARY_OPERATOR
  };
  /**
   * @pure @struct Node
   * @brief Specifies generic node
   */
  struct Node
  {
    Token *m_tok; ///< Default represented token

    /**
     * @brief Returns node as string representation
     * 
     * @return string node representation
     */
    virtual std::string to_string() = 0;
    /**
     * @brief Returns combined lexemes of each token within each node
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
  };

  /**
   * @pure @struct ValueNode
   * @brief Specifies generic value node
   * - Used for Digits and Identifiers
   */
  struct ValueNode : virtual public Node
  {
    Token m_tok_value; ///< token value

    /**
     * @return true because a value node is a leaf
     * ? Is it though?
     */
    inline bool isLeaf() override { return true; }

    /**
     * @return false because value node has no grandchildren
     * ? Does it though?
     */
    inline bool hasGrandchildren() override { return false; }
  };

  /**
   * @pure @struct OpNode
   * @brief Specifies generic operator node
   * - Used for Operators
   */
  struct OpNode : virtual public Node
  {
    Token m_tok_op; ///< token operator

    /**
     * @return false because an operator node is not a leaf
     * ? Is it though?
     */
    inline bool isLeaf() override { return false; }
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
    std::string to_string() override;

    /**
     * @brief Returns combined lexemes of each token within each node
     * 
     * @return combined lexemes as a string
     */
    std::string to_repr() override;

    /**
     * @return Digit node type
     */
    inline NodeType getType() override { return NodeType::DIGIT; }
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
    std::string to_string() override;

    /**
     * @brief Returns combined lexemes of each token within each node
     * 
     * @return combined lexemes as a string
     */
    std::string to_repr() override;

    /**
     * @return Identifier Node Type
     */
    inline NodeType getType() override { return NodeType::IDENTIFIER; }
  };

  /**
   * @struct BinOpNode
   * @brief node specifying binary operators
   */
  struct BinOpNode final : virtual public OpNode
  {
  public:
    std::unique_ptr<Node> m_node_left; ///< left operand
    std::unique_ptr<Node> m_node_right; ///< right operand
    
    /**
     * @brief BinOpNode(tok_op)
     */
    BinOpNode(Token &tok_op);
    /**
     * @brief BinOpNode(node_left, tok_op, node_right) constructor
     */
    BinOpNode(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
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

    /**
     * @brief Returns combined lexemes of each token within each node
     * 
     * @return combined lexemes as a string
     */
    std::string to_repr() override;

    /**
     * @return true if node has grandchildren,
     * false otherwise.
     */
    bool hasGrandchildren() override;

    /**
     * @return Binary Node Type
     */
    inline NodeType getType() override { return NodeType::BINARY_OPERATOR; }

    /**
     * @return false because an operator node is not a leaf
     * ? Is it though?
     */
    inline bool isLeaf() override { return false; }
  };

  /**
   * @struct UnaOpNode
   * @brief node specifying unary operators
   */
  struct UnaOpNode final : virtual public OpNode
  {
    std::unique_ptr<Node> m_node; ///< left operand

    /**
     * @brief UnaOpNode(tok_op)
     */
    UnaOpNode(Token &tok_op);
    /**
     * @brief UnaOpNode(tok_op, node)
     */
    UnaOpNode(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
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

    /**
     * @brief Returns combined lexemes of each token within each node
     * 
     * @return combined lexemes as a string
     */
    std::string to_repr() override;

    /**
     * @return true if node has grandchildren,
     * false otherwise.
     */
    bool hasGrandchildren() override;

    /**
     * @return Unary Node Type
     */
    inline NodeType getType() override { return NodeType::UNARY_OPERATOR; }
  };
}