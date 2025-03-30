/**
 * @file mua/inc/front/Definer.hpp
 * @author Christian Santos
 * @version 1.0.0
 * @date 9/7/2024
 */

#pragma once

#include <memory>
#include <list>
#include <stack>
#include <unordered_map>

#include "Node.hpp"
#include "NodeType.hpp"
#include "BinOpNode.hpp"
#include "UnaOpNode.hpp"
#include "TokenType.hpp"
#include "Token.hpp"
#include "NameTrie.hpp"
#include "TrieNode.hpp"
#include "Position.hpp"
#include "Error.hpp"
#include "INodeFactory.hpp"
#include "NodeFactory.hpp"

namespace mua
{
  class Definer
  {
  private:
    std::stack<Node*> analyze_nodes; // for parsing using dfs
    std::unordered_map<std::string, Node*> name_table; // symbol table
    std::stack<std::unique_ptr<Node>> adjacent_nodes; // for building adjacent nodes
    std::unique_ptr<INodeFactory> node_factory;
    NameTrie name_trie;
    TrieNode* curr;
    Position pos;

    bool let_stmt;

    void err(int i, Token tok);
    void searchOneNode(Node* node);
    void analyzeTree(Node* root);
  public:
    Definer();
    /*
     * @brief analyzes parse trees to append to symbol table and modify tree accordingly
     *
     * @param root node of parse tree to analyze
     */
    void define(std::list<std::unique_ptr<Node>>* parse_trees);
    void getSymbolTable();
  };
}
