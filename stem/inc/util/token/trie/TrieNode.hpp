/**
 * @file stem/inc/util/token/trie/TrieNode.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 8/11/2024
 */
#pragma once

#include <unordered_map>
#include <string>

#include "TokenType.hpp"

namespace stem
{
  struct TrieNode
  {
    std::unordered_map<char, TrieNode> nodes;
    TokenType type = TokenType::UNKNOWN;
  };
}
