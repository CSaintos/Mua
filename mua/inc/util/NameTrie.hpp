#pragma once

#include <memory>
#include <string>

#include "TrieNode.hpp"

namespace mua
{
  class NameTrie
  {
  private:
    TrieNode root;
  public:
    TrieNode* getTrie();
    void pushName(std::string name);
  };
}
