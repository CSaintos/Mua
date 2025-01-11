/**
 * @file mua/inc/util/token/trie/TokenTrie.hpp
 * @author Christian Santos
 * @version 1.0.2
 * @date 1/10/2025
 */

#pragma once

#include <memory>
#include <string>
#include <list>

#include "TrieNode.hpp"
#include "TokenUtils.hpp"

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
