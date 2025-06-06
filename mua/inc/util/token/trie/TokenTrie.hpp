#pragma once

#include <memory>
#include <string>
#include <list>

#include "TrieNode.hpp"
#include "TokenUtils.hpp"
#include "TokenType.hpp"

namespace mua
{
  class TokenTrie
  {
  private:
    static TokenTrie instance;
    TrieNode root;
    static bool is_instanciated;
    TokenTrie();
  public:
    static TokenTrie* getInstance();
    TrieNode* getTrie();
  };
}
