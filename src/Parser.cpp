#include "Parser.hpp"

stem::Parser::Parser()
    : m_last_op(TokenType::EMPTY),
      m_last_type(TokenType::EMPTY),
      m_paren_count(0)
{}

stem::Parser::~Parser()
{}

void stem::Parser::err(int i, Token &tok)
{
  stem::SyntaxError serr;
  serr.setPos(tok.m_pos);
  serr.setDetails("Undefined");

  switch (i)
  {
  case 1:
    serr.setDetails("Expected a DIGIT or IDENTIFIER");
    std::cout << serr.to_string() << std::endl;
    break;
  case 2:
    serr.setDetails("Encountered a value after a value");
    std::cout << serr.to_string() << std::endl;
    break;
  default:
    std::cout << serr.to_string() << std::endl;
  }
  exit(1);
}

void stem::Parser::buildUnaLOp()
{
  // Extract nodes
  if (!m_node_stack.empty() && m_right_node == nullptr)
  {
    m_right_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  } 
  else if (m_node_stack.empty() && m_right_node == nullptr)
  {
    //! Error
    err(1, *m_itr);
  }

  if (!m_node_stack.empty() && m_op_node == nullptr)
  {
    m_op_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else
  {
    //! Error
    err(0, *m_itr);
  }

  // build tree branch
  m_right_node = std::make_unique<stem::UnaOpNode>(m_op_node, m_right_node);
}

void stem::Parser::buildUnaROp()
{
  // Extract nodes
  if (m_op_node == nullptr)
  {
    m_op_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else
  {
    //! Error
    err(0, *m_itr);
  }

  if (!m_node_stack.empty() && m_right_node == nullptr)
  {
    m_right_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else if (m_node_stack.empty() && m_right_node == nullptr)
  {
    //! Error
    err(1, *m_itr); // expected 1 or d
  }

  // build tree branch
  m_right_node = std::make_unique<UnaOpNode>(m_op_node, m_right_node);
}

void stem::Parser::buildBinOp()
{
  // Extract nodes
  if (m_right_node == nullptr)
  {
    m_right_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }

  if (!m_node_stack.empty())
  {
    m_op_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else
  {
    m_op_node.release();
  }

  if (!m_node_stack.empty())
  {
    m_left_node = std::move(m_node_stack.top());
    m_node_stack.pop();
  }
  else if (m_op_node != nullptr)
  {
    if (m_curr_node != nullptr)
    {
      m_left_node = std::move(m_curr_node);
    }
    else
    {
      //! Error
      err(1, *m_itr); // expected d or i
    }
  }
  
  // Build tree branch
  if (m_left_node != nullptr)
  {
    m_right_node = std::make_unique<BinOpNode>(m_left_node, m_op_node, m_right_node);
  }
}

void stem::Parser::toParseTree()
{
  bool loop = true;
  while (!m_node_stack.empty() && loop)
  {
    TokenType type_top = m_node_stack.top()->m_tok->m_type;

    switch (type_top)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      if (m_node_stack.size() > 2)
      {
        buildBinOp();
      }
      else if (m_node_stack.size() == 2)
      {
        buildUnaLOp();
      }
      else if (m_node_stack.size() == 1)
      {
        m_right_node = std::move(m_node_stack.top());
        m_node_stack.pop();
      }
      break;
    case TokenType::PLUS:
    case TokenType::MINUS:
      if (m_right_node != nullptr)
      {
        if (m_node_stack.size() > 1)
        {
          buildBinOp();
        }
        else if (m_node_stack.size() == 1)
        {
          buildUnaLOp();
        }
        else
        {
          err(0, *m_itr);
        }
      }
      else
      {
        err(0, *m_itr); //? don't know when this happens
        //buildUnaOp();
      }
      break;
    case TokenType::ASTERISK:
    case TokenType::FSLASH:
    case TokenType::CARET:
      if (m_right_node != nullptr)
      {
        buildBinOp();
      }
      else
      {
        //! Error
        err(1, *m_itr); // expected d or 1
      }
      break;
    case TokenType::LPAREN:
      m_unaop_node = dynamic_cast<stem::UnaOpNode*>(m_node_stack.top().get());
      if (m_unaop_node->m_node == nullptr)
      {
        if (m_right_node != nullptr)
        {
          m_node_stack.push(std::move(m_right_node));
        }
        loop = false;
      }
      else
      {

      }
      // TODO check if parenthesis contains a node
      // If it doesn't contain a node, reinsert right node (if not empty) into stack and break loop
      //? else apply binary operation
      break;
    default:
      //! Error
      err(1, *m_itr); // expected d or i
    }
  }

  if (m_curr_node == nullptr)
  {
    m_curr_node = std::move(m_right_node);
  }
}

void stem::Parser::scanOneToken()
{
  switch (m_itr->m_type)
  {
  case TokenType::DIGIT:
    switch (m_last_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      //! Error
      err(2, *m_itr); // value after value err
      break;
    default:
      m_last_type = m_itr->m_type;
      m_node_stack.push(std::make_unique<DigitNode>(*m_itr));
      break;
    }
    break;
  case TokenType::IDENTIFIER:
    switch (m_last_type)
    {
    case TokenType::DIGIT:
    case TokenType::IDENTIFIER:
      //! Error
      err(2, *m_itr); // value after value err
      break;
    default:
      m_last_type = m_itr->m_type;
      m_node_stack.push(std::make_unique<IdentifierNode>(*m_itr));
      break;
    }
    break;
  case TokenType::MINUS:
  case TokenType::PLUS:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      m_last_type = m_itr->m_type;
      m_last_op = m_last_type;
      m_node_stack.push(std::make_unique<UnaOpNode>(*m_itr));
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        // empty stack and build tree
        toParseTree();
        // add token to stack
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      default:
        // error
        err(0, *m_itr); // unknown
        break;
      }
      break;
    }
    break;
  case TokenType::FSLASH:
  case TokenType::ASTERISK:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      //! Error
      err(1, *m_itr); // expected d or i
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
      case TokenType::PLUS:
      case TokenType::MINUS:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        // empty stack and build tree
        toParseTree();
        // add token to stack
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      default:
        // error unknown
        err(0, *m_itr);
        break;
      }
      break;
    }
    break;
  case TokenType::CARET:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      //! Error
      err(1, *m_itr); // expected d or i
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
      case TokenType::LPAREN:
      case TokenType::RPAREN:
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<BinOpNode>(*m_itr));
        break;
      default:
        err(0, *m_itr);
        break;
      }
      break;
    }
    break;
  case TokenType::LPAREN:
    switch (m_last_type)
    {
    case TokenType::RPAREN:
    case TokenType::DIGIT:
      //! Error
      err(0, *m_itr); // expected op or i
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::EMPTY:
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_node_stack.push(std::make_unique<UnaOpNode>(*m_itr));
        m_paren_count++;
        break;
      default:
        //? Error
        err(0, *m_itr); // unknown
        break;
      }
      break;
    }
    break;
  case TokenType::RPAREN:
    switch (m_last_type)
    {
    case TokenType::EMPTY:
      //! Error
      err(0, *m_itr); // not a valid stmt
      break;
    default:
      switch (m_last_op)
      {
      case TokenType::PLUS:
      case TokenType::MINUS:
      case TokenType::ASTERISK:
      case TokenType::FSLASH:
      case TokenType::CARET:
      case TokenType::LPAREN:
        // empty stack and build tree
        toParseTree();
        // attach resulting node to LPAREN node
        buildUnaLOp();
        // add nodes to tree
        toParseTree();
        // label last token
        m_last_type = m_itr->m_type;
        m_last_op = m_last_type;
        m_paren_count--;
        break;
      default:
        //? Error
        err(0, *m_itr); // unknown
        break;
      }
      break;
    }
    break;
  default:
    // TODO throw unknown syntax error
    err(0, *m_itr);
    break;
  }
}

void stem::Parser::parse(std::list<stem::Token> *token_stream)
{
  // initialize member variables
  m_token_stream = token_stream;
  m_curr_node.release(); //? is this a good idea?
  
  for (m_itr = token_stream->begin(); m_itr != token_stream->end(); ++m_itr)
  {
    //std::cout << (*m_itr).to_string() << std::endl;
    // parse single token
    scanOneToken();
    // end of parse
  }

  toParseTree();
}

stem::Node* stem::Parser::getParseTree()
{
  if (m_curr_node == nullptr)
    return nullptr;
  return &(*m_curr_node);
}
