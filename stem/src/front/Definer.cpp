#include "Definer.hpp"

using namespace std;
using namespace stem;

Definer::Definer()
  : let_stmt(false),
    name_trie(),
    name_table()
//    curr(nullptr)
{}

void Definer::init()
{
  
}

void Definer::searchOneNode(Node* node)
{
  cout << node->to_string() << endl;
  switch(node->getType())
  {
  case NodeType::BINARY_OPERATOR:
  {
    BinOpNode* bin_op_node = dynamic_cast<BinOpNode*>(node);
    analyze_nodes.push(bin_op_node->m_node_left.get());
    analyze_nodes.push(bin_op_node->m_node_right.get());
    if (bin_op_node->m_tok.type == TokenType::EQUAL &&
      let_stmt)
    {
      Token left_token = bin_op_node->m_node_left->m_tok;
      if (left_token.type == TokenType::IDENTIFIER)
      {
        name_trie.pushName(left_token.lexemes);
        name_table.insert({left_token.lexemes, bin_op_node->m_node_right.get()});
      }
    }
    break;
  }
  case NodeType::UNARY_OPERATOR:
  {
    UnaOpNode* una_op_node = dynamic_cast<UnaOpNode*>(node);
    analyze_nodes.push(una_op_node->m_node.get());
    if (una_op_node->m_tok.type == TokenType::LET)
    {
      let_stmt = true;
    }
    break;
  }
  default:
  {
    break;
  }
  }
}

void Definer::analyzeTree(Node* root)
{
  let_stmt = false;
  searchOneNode(root);

  while (!analyze_nodes.empty())
  {
    Node* curr_node = analyze_nodes.top();
    analyze_nodes.pop();
    searchOneNode(curr_node);
  }
}

void Definer::define(vector<unique_ptr<Node>>* parse_trees)
{
  this->parse_trees = parse_trees;
  
  for (int i = 0; i < parse_trees->size(); i++)
  {
    analyzeTree((*parse_trees)[i].get());
  }
  cout << name_table.size() << endl;
}

void Definer::getSymbolTable()
{

}
