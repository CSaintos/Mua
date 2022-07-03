/**
 * @brief This file is part of {{ stem.inc.front }}
 * 
 * @file Parser.hpp
 * @author Christian Santos
 * @version 1.0.8 
 * @date 6/1/2022
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
    
    std::unique_ptr<stem::Node> m_curr_node; ///< holds pointer to current/root node of tree
    std::unique_ptr<stem::Node> m_left_node; ///< holds left node for binary operators
    std::unique_ptr<stem::Node> m_right_node; ///< holds right node for operators
    std::unique_ptr<stem::Node> m_op_node; ///< holds op node for operators

    stem::TokenType m_last_type; ///< last token type iterated
    stem::TokenType m_last_op; ///< last operator token type iterated

    stem::UnaOpNode *m_unaop_node; ///< for building parantheses nodes

    int m_paren_count; ///< number of Lparens not closed

    /**
     * @brief prints error to console
     * 
     * @param i error option
     * @param tok token that caused error
     */
    void err(int i, Token &tok); //? Temporary syntax error

    /**
     * @brief builds a unary op node where operator is on the left side
     */
    void buildUnaLOp();
    /**
     * @brief builds a unary op node where operator is on the right side
     */
    void buildUnaROp();
    /**
     * @brief builds a binary op node
     */
    void buildBinOp();
    /**
     * @brief builds parse tree by emptying out m_node_stack or until stopped
     */
    void toParseTree();
    /**
     * @brief scans a single token, converts into a node and adds it to m_node_stack
     * @note it uses m_last_type and m_last_op to decide whether to parse the tree at that location or not
     */
    void scanOneToken();
  public:
    /**
     * @brief Parser() constructor
     * @see ~Parser()
     */
    Parser();
    /**
     * @brief ~Parser() destructor
     * @see Parser()
     */
    ~Parser();

    /**
     * @brief parses the token stream and converts it into a parse tree
     * 
     * @param token_stream the list of tokens to be parsed
     */
    void parse(std::list<stem::Token> *token_stream);
    /**
     * @brief returns a pointer to the root node of the parse tree
     * 
     * @return root node of type Node pointer
     */
    Node* getParseTree();
  };
}