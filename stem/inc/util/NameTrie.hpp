/**
 * @file stem/inc/util/NameTrie.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 9/10/2024
 */

#pragma once

#include <string>

#include "TrieNode.hpp"

namespace stem
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
