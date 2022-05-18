/**
 * @brief This file is part of {{ stem.inc }}
 * 
 * @file Parser.hpp
 * @author Christian Santos
 * @version 1.0.0 5/18/2022
 */

#pragma once

#include <list>

#include "Error.hpp"
#include "Token.hpp"

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

  public:
    Parser();
    ~Parser();

    bool parse(std::list<stem::Token> *token_stream);
  };
}