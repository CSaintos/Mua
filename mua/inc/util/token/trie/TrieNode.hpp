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
