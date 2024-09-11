#include "NameTrie.hpp"

using namespace stem;
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
      curr->nodes.insert({c, TrieNode()});
    }
    curr = &(curr->nodes[c]);
  }
  curr->lexemes = name;
}
