/**
 * @brief This file is part of {{ stem.inc }}
 * 
 * @file Parser.hpp
 * @author Christian Santos
 * @version 1.0.0 5/18/2022
 */

#pragma once

#include <memory>
#include <list>

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
    /// pointer to token stream
    std::list<stem::Token> *m_token_stream;
    /// iterator to current element in token stream
    std::list<stem::Token>::iterator m_itr;
    /// iterator to last element in token stream
    std::list<stem::Token>::iterator m_end;


    std::unique_ptr<stem::Node> m_root_node;
    std::unique_ptr<stem::Node> m_curr_node;
    std::unique_ptr<stem::Node> m_left_node;
    std::unique_ptr<stem::Node> m_right_node;

    stem::Token m_tok_op;

    void advance();
    void factor();
    void term();
    void expr();
  public:
    Parser();
    ~Parser();

    void parse(std::list<stem::Token> *token_stream);
    Node* getParseTree();
  };
}