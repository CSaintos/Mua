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
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "node_state/BinPlus.hpp"
#include "node_state/UnaPlus.hpp"
#include "node_state/UnaMinus.hpp"
#include "node_state/BinMinus.hpp"
#include "node_state/Asterisk.hpp"
#include "node_state/FSlash.hpp"
#include "node_state/Percent.hpp"
#include "node_state/Caret.hpp"
#include "node_state/Paren.hpp"
#include "node_state/Equal.hpp"
#include "node_state/Let.hpp"
#include "node_state/Semicolon.hpp"

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
