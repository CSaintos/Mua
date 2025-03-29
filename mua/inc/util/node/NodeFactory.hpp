/**
 * @file mua/inc/util/node/NodeFactory.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 3/27/2025
 */
#pragma once

#include <iostream>
#include <memory>

#include "INodeFactory.hpp"
#include "TokenType.hpp"
#include "TokenUtils.hpp"
#include "Token.hpp"
#include "NodeType.hpp"
#include "Node.hpp"
#include "ValueNode.hpp"
#include "BinPlus.hpp"
#include "UnaPlus.hpp"
#include "UnaMinus.hpp"
#include "BinMinus.hpp"
#include "Asterisk.hpp"
#include "FSlash.hpp"
#include "Percent.hpp"
#include "Caret.hpp"
#include "Paren.hpp"
#include "Equal.hpp"
#include "Let.hpp"
#include "Semicolon.hpp"

namespace mua
{
  class NodeFactory : public INodeFactory
  {
  public:
    std::unique_ptr<Node> produceNode(Token &token, std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_right, NodeType node_type = NodeType::BINARY_OPERATOR) override;
    std::unique_ptr<Node> produceNode(TokenType token_type, NodeType node_type = NodeType::BINARY_OPERATOR) override;
    std::unique_ptr<Node> produceNode(TokenType token_type, std::unique_ptr<Node> &node) override;
    std::unique_ptr<Node> produceNode(TokenType token_type, std::unique_ptr<Node> &node_left, std::unique_ptr<Node> &node_right) override;
    std::unique_ptr<Node> produceNode(Token &token, NodeType node_type = NodeType::BINARY_OPERATOR) override;
    std::unique_ptr<Node> produceNode(Token &token, std::unique_ptr<Node> &node) override;
  };
}
