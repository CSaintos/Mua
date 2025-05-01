#include "NameTrie.hpp"

using namespace mua;
using namespace std;

TrieNode* NameTrie::getTrie()
{
  return &root;
}

void NameTrie::pushName(string name)
{
  TrieNode* curr = &root;
  for (char c : name)
  {
    if (curr->nodes.count(c) == 0)
    {
      curr->nodes.insert({c, std::make_unique<TrieNode>()});
    }
    curr = curr->nodes[c].get();
  }
  curr->lexemes = name;
}
