#pragma once

#include <memory>

#include "TokenType.hpp"
#include "Token.hpp"
#include "NodeType.hpp"
#include "Node.hpp"

namespace mua
{
  class Node; // Forward declaration (fixes circular dependency compilation error)
  /**
   * @pure @class INodeFactory
   * @brief NodeFactory Interface
   */
  class INodeFactory
  {
  public:
    virtual ~INodeFactory() = default;

    virtual std::unique_ptr<Node> produceNode(Token &token, std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_right, NodeType node_type = NodeType::BINARY_OPERATOR) = 0;
    virtual std::unique_ptr<Node> produceNode(TokenType token_type, NodeType node_type = NodeType::BINARY_OPERATOR) = 0;
    virtual std::unique_ptr<Node> produceNode(TokenType token_type, std::unique_ptr<Node> &node) = 0;
    virtual std::unique_ptr<Node> produceNode(TokenType token_type, std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_right) = 0;
    virtual std::unique_ptr<Node> produceNode(Token &token, NodeType node_type = NodeType::BINARY_OPERATOR) = 0;
    virtual std::unique_ptr<Node> produceNode(Token &token, std::unique_ptr<Node> &node) = 0;
  };
}
