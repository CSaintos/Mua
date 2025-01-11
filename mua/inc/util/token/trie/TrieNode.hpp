/**
 * @file mua/inc/util/token/trie/TrieNode.hpp
 * @author Christian Santos
 * @version 1.0.3
 * @date 1/10/2025
 */
#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "TokenType.hpp"

namespace mua
{
  struct TrieNode
  {
    std::unordered_map<char, std::unique_ptr<TrieNode>> nodes;
    TokenType type = TokenType::EMPTY;
    std::string lexemes;
  };
}
