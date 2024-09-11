/**
 * @file stem/inc/front/Parser.hpp
 * @author Christian Santos
 * @version 1.2.0
 * @date 9/7/2024
 */

#pragma once

#include <iostream>
#include <memory>
#include <list>
#include <stack>
#include <vector>

#include "Error.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "BinOpNode.hpp"
#include "ValueNode.hpp"

namespace stem
{
  /**
   * @class Parser
   * 
   * @brief Handles converting token stream to parse tree.
   * Implemented as an LR parser
   */ 
  class Parser
  {
  private:
    /// vector of parse trees
    std::vector<std::unique_ptr<stem::Node>> parse_trees;
    /// stack of nodes
    std::stack<std::unique_ptr<stem::Node>> node_stack;
    /// stack of nodes of unclosed parenthesis
    std::stack<stem::Node*> open_parens;
    /// pointer to token stream
    std::list<stem::Token> *token_stream;
    /// iterator to current element in token stream
    std::list<stem::Token>::iterator itr;
    
    std::unique_ptr<stem::Node> curr_node; ///< holds pointer to current/root node of tree
    std::unique_ptr<stem::Node> left_node; ///< holds left node for binary operators
    std::unique_ptr<stem::Node> right_node; ///< holds right node for operators
    std::unique_ptr<stem::Node> op_node; ///< holds op node for operators

    stem::TokenType last_type; ///< last token type iterated
    stem::TokenType last_op; ///< last operator token type iterated

    stem::UnaOpNode *unaop_node; ///< for building parantheses nodes

    int equal_count;
    
    bool let_stmt; ///< flag that current stmt is a let_stmt
    bool right_paren; ///< flag that right parenthesis was found
    bool end_of_expr; ///< flag that end of expression was found
    bool end_of_stmt; ///< flag that end of statement was found (semicolon)

    /**
     * @brief prints error to console
     * 
     * @param i error option
     * @param tok token that caused error
     */
    void err(int i, Token &tok); //? Temporary syntax error

    /**
     * @brief adds exclusive parent node to m_node_queue
     */
    void addExclusiveParent(stem::Node *node);
    /**
     * @brief builds parse tree by emptying out m_node_stack or until stopped
     */
    void toParseTree();
    /**
     * @brief scans a single token, converts into a node and adds it to m_node_stack
     * @note it uses m_last_type and m_last_op to decide whether to parse the tree at that location or not
     */
    void scanOneToken();
    /**
     * @brief propagates parse tree into vector of parse trees
     */
    void propagateTree();
  public:
    /**
     * @brief Parser() constructor
     * @see ~Parser()
     */
    Parser();

    /**
     * @brief parses the token stream and converts it into a parse tree
     * 
     * @param token_stream the list of tokens to be parsed
     */
    void parse(std::list<stem::Token> *token_stream);
    /**
     * @brief returns a pointer to vector of completed parse trees
     * 
     * @return pointer to vector of completed parse trees
     */
    //std::vector<stem::Node*> getParseTrees();
    inline std::vector<std::unique_ptr<stem::Node>>* getParseTrees() { return &parse_trees; }
  };
}
