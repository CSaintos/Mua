/**
 * @file stem/inc/util/node/op_node/una_node/UnaOpNode.hpp
 * @author Christian Santos
 * @version 1.0.1 
 * @date 9/21/2024
*/

#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "Node.hpp"
#include "Token.hpp"
#include "NodeType.hpp"
#include "TokenType.hpp"

namespace stem
{
  /**
   * @struct UnaOpNode
   * @brief node specifying unary operators
   */
  struct UnaOpNode : public Node
  {
    std::unique_ptr<Node> node; ///< left operand

    /**
     * @brief UnaOpNode(tok_op)
     */
    UnaOpNode(Token &tok_op);
    /**
     * @brief UnaOpNode(node_op, node)
     */
    UnaOpNode(std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node);
    /**
     * @brief UnaOpNode(tok_op, node)
    */
    UnaOpNode(Token &tok_op, std::unique_ptr<Node> &node);
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
    
    /**
     * @return false, an operator node is not a leaf
     **/
    inline bool isLeaf() override { return false; }

    void interpret() override;   
  };
}
