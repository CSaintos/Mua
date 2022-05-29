/**
 * @brief This file is part of {{ stem.inc }}
 * 
 * @file Parser.hpp
 * @author Christian Santos
 * @version 1.0.7 5/29/2022
 */

#pragma once

#include <iostream>
#include <memory>
#include <list>
#include <stack>

#include "Error.hpp"
#include "Token.hpp"
#include "Node.hpp"

namespace stem
{
  /**
   * @class Parser
   * 
   * @brief Handles converting token stream to parse tree
   */ 
  class Parser
  {
  private:
    /// stack of nodes
    std::stack<std::unique_ptr<stem::Node>> m_node_stack;
    //^ Do not do stack<Node> as that causes "object slicing"
    /// pointer to token stream
    std::list<stem::Token> *m_token_stream;
    /// iterator to current element in token stream
    std::list<stem::Token>::iterator m_itr;
    
    std::unique_ptr<stem::Node> m_curr_node;
    std::unique_ptr<stem::Node> m_left_node;
    std::unique_ptr<stem::Node> m_right_node;
    std::unique_ptr<stem::Node> m_op_node;

    stem::TokenType m_last_type;
    stem::TokenType m_last_op;

    stem::UnaOpNode *m_unaop_node;

    int m_paren_count;

    void err(int i); //? Temporary syntax error

    void buildUnaLOp();
    void buildUnaROp();
    void buildBinOp(); // TODO err checking
    void toParseTree();
    void scanOneToken();
  public:
    Parser();
    ~Parser();

    void parse(std::list<stem::Token> *token_stream);
    Node* getParseTree();
  };
}