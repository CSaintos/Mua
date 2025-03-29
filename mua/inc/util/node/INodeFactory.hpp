/**
 * @file mua/inc/util/node/INodeFactory.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 3/27/2025
 */
#pragma once

#include <memory>

#include "TokenType.hpp"
#include "Token.hpp"
#include "NodeType.hpp"
#include "Node.hpp"

namespace mua
{
  /**
   * @pure @class INodeFactory
   * @brief NodeFactory Interface
   */
  class INodeFactory
  {
  public:
    virtual ~INodeFactory() = default;

    virtual std::unique_ptr<Node> produceNode(Token &token, NodeType node_type = NodeType::BINARY_OPERATOR) = 0;
    virtual std::unique_ptr<Node> produceNode(TokenType token_type, NodeType node_type = NodeType::BINARY_OPERATOR) = 0;
  };
}
