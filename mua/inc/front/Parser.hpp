#pragma once

#include <iostream>
#include <memory>
#include <list>
#include <stack>
#include <optional>
#include <unordered_set>

#include "Error.hpp"
#include "Token.hpp"
#include "TokenType.hpp"
#include "Node.hpp"
#include "UnaOpNode.hpp"
#include "BinOpNode.hpp"
#include "INodeFactory.hpp"
#include "NodeFactory.hpp"

namespace mua
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
    /// list of parse trees
    std::list<std::unique_ptr<Node>> parse_trees;
    /// stack of nodes
    std::stack<std::unique_ptr<Node>> node_stack;
    /// stack of nodes of unclosed parenthesis
    std::stack<Node*> open_parens;
    /// stack of operators before lparens
    std::stack<Node*> op_b4_paren;
    /// pointer to token stream
    std::list<Token> *token_stream;
    /// iterator to current element in token stream
    std::list<Token>::iterator itr;
    /// pemd in pemdas
    std::unordered_set<TokenType> pemd;
    /// pe in pemdas
    std::unordered_set<TokenType> pe;
    
    /// Holds pointer to current/root node of tree
    /// Keeps node_stack empty when needed
    std::unique_ptr<Node> left_node; ///< holds left node for binary operators
    std::unique_ptr<Node> right_node; ///< holds right node for operators
    std::unique_ptr<Node> op_node; ///< holds op node for operators
    std::unique_ptr<BinOpNode> bin_op;
    std::unique_ptr<UnaOpNode> una_op;
    std::unique_ptr<INodeFactory> node_factory;

    TokenType last_type; ///< last token type iterated
    TokenType last_op; ///< last operator token type iterated

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
     * @brief builds parse tree by emptying out m_node_stack or until stopped
     */
    void toParseTree(TokenType precedence_type);
    /**
     * @brief scans a single token, converts into a node and adds it to m_node_stack
     * @note it uses m_last_type and m_last_op to decide whether to parse the tree at that location or not
     */
    void scanOneToken();
    /**
     * @brief propagates parse tree into list of parse trees
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
    void parse(std::list<Token> *token_stream);
    
    void checkSemicolonError();
    /**
     * @brief returns a pointer to list of completed parse trees
     * 
     * @return pointer to list of completed parse trees
     */
    inline std::list<std::unique_ptr<Node>>* getParseTrees() { return &parse_trees; }
  };
}
