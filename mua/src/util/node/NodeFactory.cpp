#include "NodeFactory.hpp"

using namespace std;
using namespace mua;


unique_ptr<Node> NodeFactory::produceNode(Token &token, unique_ptr<Node> &node_left, unique_ptr<Node> &node_right, NodeType node_type)
{
  switch (token.type)
  {
  case TokenType::COMMENT:
  case TokenType::EMPTY:
  case TokenType::UNKNOWN:
    cout << "NodeFactory Error: Cannot create Node of TokenType " + TokenUtils::m_TS_map[token.type] << endl;
    break;
  case TokenType::DIGIT:
  case TokenType::IDENTIFIER:
    return std::make_unique<ValueNode>(this, token);
    break;
  case TokenType::PLUS:
    if (node_type == NodeType::BINARY_OPERATOR)
    {
      if (node_right != nullptr)
      {
        return std::make_unique<BinPlus>(this, node_left, token, node_right);
      }
      return std::make_unique<BinPlus>(this, token);
    }
    else if (node_type == NodeType::UNARY_OPERATOR)
    {
      if (node_left != nullptr)
      {
        return std::make_unique<UnaPlus>(this, token, node_left);
      }
      return std::make_unique<UnaPlus>(this, token);
    }
    else
    {
      cout << "NodeFactory Error: NodeType VALUE is invalid for TokenType " + TokenUtils::m_TS_map[token.type] << endl; 
    }
    break;
  case TokenType::MINUS:
    if (node_type == NodeType::BINARY_OPERATOR)
    {
      if (node_right != nullptr)
      {
        return std::make_unique<BinMinus>(this, node_left, token, node_right);
      }
      return std::make_unique<BinMinus>(this, token);
    }
    else if (node_type == NodeType::UNARY_OPERATOR)
    {
      if (node_left != nullptr)
      {
        return std::make_unique<UnaMinus>(this, token, node_left);
      }
      return std::make_unique<UnaMinus>(this, token);
    }
    else
    {
      cout << "NodeFactory Error: NodeType VALUE is invalid for TokenType " + TokenUtils::m_TS_map[token.type] << endl;
    }
    break;
  case TokenType::ASTERISK:
  case TokenType::ADJACENT:
    if (node_right != nullptr)
    {
      return std::make_unique<Asterisk>(this, node_left, token, node_right);
      }
    return std::make_unique<Asterisk>(this, token);
    break;
  case TokenType::FSLASH:
    if (node_right != nullptr)
    {
      return std::make_unique<FSlash>(this, node_left, token, node_right);
    }
    return std::make_unique<FSlash>(this, token);
    break;
  case TokenType::PERCENT:
    if (node_right != nullptr)
    {
      return std::make_unique<Percent>(this, node_left, token, node_right);
    }
    return std::make_unique<Percent>(this, token);
    break;
  case TokenType::CARET:
    if (node_right != nullptr)
    {
      return std::make_unique<Caret>(this, node_left, token, node_right);
    }
    return std::make_unique<Caret>(this, token);
    break;
  case TokenType::LPAREN:
  case TokenType::RPAREN:
    if (node_left != nullptr)
    {
      return std::make_unique<Paren>(this, token, node_left);
    }
    return std::make_unique<Paren>(this, token);
    break;
  case TokenType::EQUAL:
    if (node_right != nullptr)
    {
      return std::make_unique<Equal>(this, node_left, token, node_right);
    }
    return std::make_unique<Equal>(this, token);
    break;
  case TokenType::LET:
    if (node_left != nullptr)
    {
      return std::make_unique<Let>(this, token, node_left);
    }
    return std::make_unique<Let>(this, token);
    break;
  case TokenType::SEMICOLON:
    if (node_left != nullptr)
    {
      return std::make_unique<Semicolon>(this, token, node_left);
    }
    return std::make_unique<Semicolon>(this, token);
    break;
  default:
    cout << "NodeFactory Error: Unrecognized TokenType " + TokenUtils::m_TS_map[token.type] << endl;
    break;
  }
  return nullptr;
}

unique_ptr<Node> NodeFactory::produceNode(TokenType token_type, NodeType node_type)
{
  Token place_holder; 
  place_holder.type = token_type;
  unique_ptr<Node> empty_node = nullptr;
  return produceNode(place_holder, empty_node, empty_node, node_type);
}

unique_ptr<Node> NodeFactory::produceNode(TokenType token_type, unique_ptr<Node> &node)
{
  Token place_holder;
  place_holder.type = token_type;
  return produceNode(place_holder, node);
}

unique_ptr<Node> NodeFactory::produceNode(TokenType token_type, unique_ptr<Node> &node_left, unique_ptr<Node> &node_right)
{
  Token place_holder;
  place_holder.type = token_type;
  return produceNode(place_holder, node_left, node_right);
}

unique_ptr<Node> NodeFactory::produceNode(Token &token, NodeType node_type)
{
  unique_ptr<Node> empty_node = nullptr;
  return produceNode(token, empty_node, empty_node, node_type);
}

unique_ptr<Node> NodeFactory::produceNode(Token &token, unique_ptr<Node> &node)
{
  unique_ptr<Node> empty_node = nullptr;
  return produceNode(token, node, empty_node, NodeType::UNARY_OPERATOR);
}
