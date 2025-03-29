#include "NodeFactory.hpp"

using namespace std;
using namespace mua;


unique_ptr<Node> NodeFactory::produceNode(Token &token, NodeType node_type)
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
    return std::make_unique<ValueNode>(token);
    break;
  case TokenType::PLUS:
    if (node_type == NodeType::BINARY_OPERATOR)
    {
      return std::make_unique<BinPlus>(token);
    }
    else if (node_type == NodeType::UNARY_OPERATOR)
    {
      return std::make_unique<UnaPlus>(token);
    }
    else
    {
      cout << "NodeFactory Error: NodeType VALUE is invalid for TokenType " + TokenUtils::m_TS_map[token.type] << endl; 
    }
    break;
  case TokenType::MINUS:
    if (node_type == NodeType::BINARY_OPERATOR)
    {
      return std::make_unique<BinMinus>(token);
    }
    else if (node_type == NodeType::UNARY_OPERATOR)
    {
      return std::make_unique<UnaMinus>(token);
    }
    else
    {
      cout << "NodeFactory Error: NodeType VALUE is invalid for TokenType " + TokenUtils::m_TS_map[token.type] << endl;
    }
    break;
  case TokenType::ASTERISK:
  case TokenType::ADJACENT:
    return std::make_unique<Asterisk>(token);
    break;
  case TokenType::FSLASH:
    return std::make_unique<FSlash>(token);
    break;
  case TokenType::PERCENT:
    return std::make_unique<Percent>(token);
    break;
  case TokenType::CARET:
    return std::make_unique<Caret>(token);
    break;
  case TokenType::LPAREN:
  case TokenType::RPAREN:
    return std::make_unique<Paren>(token);
    break;
  case TokenType::EQUAL:
    return std::make_unique<Equal>(token);
    break;
  case TokenType::LET:
    return std::make_unique<Let>(token);
    break;
  case TokenType::SEMICOLON:
    return std::make_unique<Semicolon>(token);
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
  return produceNode(place_holder, node_type);
}
