#pragma once

#include <memory>
#include <string>
#include <unordered_set>

#include "Token.hpp"
#include "TokenType.hpp"
#include "NodeType.hpp"
#include "Node.hpp"
#include "INodeFactory.hpp"
#include "InterpretType.hpp"

namespace mua
{
  /**
   * @struct BinOpNode
   * @brief node specifying binary operators
   */
  struct BinOpNode : public Node
  {
  public:
    std::unique_ptr<Node> node_left; ///< left operand
    std::unique_ptr<Node> node_right; ///< right operand
    
    /**
     * @brief BinOpNode(tok_op)
     */
    BinOpNode(INodeFactory *node_factory, Token &tok_op);
    /**
     * @brief BinOpNode(node_left, node_op, node_right) constructor
     */
    BinOpNode(std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_op, std::unique_ptr<Node> &node_right);
    /**
     * @brief BinOpNode(node_left, tok_op, node_right) 
    */
    BinOpNode(INodeFactory *node_factory, std::unique_ptr<Node> &node_left, Token &tok_op, std::unique_ptr<Node> &node_right);

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
     * @return false, an operator node is not a leaf
     **/
    inline bool isLeaf() override { return false; } 

    bool interpret(const std::unordered_set<InterpretType> &flags = {}) override;

    std::unique_ptr<Node> copy() override;
  };
}
