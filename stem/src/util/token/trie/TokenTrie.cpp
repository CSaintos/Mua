#include "TokenTrie.hpp"

using namespace stem;
using namespace std;

TrieNode* TokenTrie::getTrie()
{
  if (TokenTrie::isInstanciated) return &root;
  
  list<string> token_strings;
  for (pair<string, TokenType> kv : TokenUtils::m_RT_map)
  {
    token_strings.push_back(kv.first);
  }

  for (string token_string : token_strings)
  {
    TrieNode* curr = &root;
    for (char c : token_string)
    {
      if (curr->nodes.count(c) == 0)
      {
        curr->nodes.insert({{c, TrieNode()}});
      }
      curr = &(curr->nodes[c]);
    }
    curr->type = TokenUtils::m_RT_map[token_string];
  }

  return &root; 
}
