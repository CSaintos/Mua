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
#include "bin_node/BinPlus.hpp"
#include "una_node/UnaPlus.hpp"
#include "una_node/UnaMinus.hpp"
#include "bin_node/BinMinus.hpp"
#include "bin_node/Asterisk.hpp"
#include "bin_node/FSlash.hpp"
#include "bin_node/Percent.hpp"
#include "bin_node/Caret.hpp"
#include "una_node/Paren.hpp"
#include "bin_node/Equal.hpp"
#include "una_node/Let.hpp"
#include "una_node/Semicolon.hpp"

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
