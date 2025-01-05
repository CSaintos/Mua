/**
 * @file mua/inc/util/node/NodeUtils.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 10/1/2024
 */
#pragma once

#include <memory>

#include "Node.hpp"
#include "NodeType.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"

namespace mua
{
  class NodeUtils
  {
  public:
    static void replaceNode(Node* to_replace, std::unique_ptr<Node> &replace_with);
  };
}
