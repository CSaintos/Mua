#include "Definer.hpp"

using namespace std;
using namespace stem;

Definer::Definer()
  : let_stmt(false),
    name_trie(),
    name_table(),
    curr(nullptr)
{}

void Definer::err(int i, Token tok)
{
  Error derr(
    pos,
    "SemanticError",
    "Undefined"
  );

  switch (i)
  {
  case 1:
    derr.setDetails("Undeclared variable " + tok.to_string() + ".");
    break;
  case 2:
    derr.setDetails("Parent type is not listed.");
    break;
  default:
    break;
  }

  cout << derr.to_string() << endl;
}

void Definer::searchOneNode(Node* node)
{
  //cout << node->to_string() << endl; // DEBUG
  switch(node->getType())
  {
  case NodeType::BINARY_OPERATOR:
  {
    BinOpNode* bin_op_node = static_cast<BinOpNode*>(node);
    analyze_nodes.push(bin_op_node->node_left.get());
    analyze_nodes.push(bin_op_node->node_right.get());
    if (bin_op_node->tok.type == TokenType::EQUAL &&
      let_stmt)
    {
      Token left_token = bin_op_node->node_left->tok;
      if (left_token.type == TokenType::IDENTIFIER)
      {
        name_trie.pushName(left_token.lexemes);
        name_table.insert({left_token.lexemes, bin_op_node->node_right.get()});
      }
    }
    break;
  }
  case NodeType::UNARY_OPERATOR:
  {
    UnaOpNode* una_op_node = static_cast<UnaOpNode*>(node);
    analyze_nodes.push(una_op_node->node.get());
    if (una_op_node->tok.type == TokenType::LET)
    {
      let_stmt = true;
    }
    break;
  }
  case NodeType::VALUE:
  {
    if (let_stmt && node->parent != nullptr &&
      node->parent->tok.type == TokenType::LET)
    {
      name_trie.pushName(node->tok.lexemes);
      name_table.insert({node->tok.lexemes, nullptr});
    }
    else if (node->tok.type == TokenType::IDENTIFIER)
    {
      curr = name_trie.getTrie();
      pos = node->tok.pos;
      pos.column_nums[1] = pos.column_nums[0];
      pos.column_nums[1]--;
      for (char c : node->tok.lexemes)
      {
        pos.column_nums[1]++;
        if (curr->nodes.count(c) == 1)
        {
          curr = &curr->nodes[c];
        }
        else if (curr != name_trie.getTrie())
        {
          Token tok;
          tok.type = TokenType::IDENTIFIER;
          tok.pos = pos;
          tok.lexemes = curr->lexemes;
          adjacent_nodes.push(std::make_unique<ValueNode>(tok));
          
          curr = name_trie.getTrie();
          pos.column_nums[0] = pos.column_nums[1];
          if (curr->nodes.count(c) == 1)
          {
            curr = &curr->nodes[c];
          }
          else
          {
            Token err_tok;
            err_tok.type = TokenType::IDENTIFIER;
            err_tok.pos = pos;
            err_tok.lexemes = c;
            err(1, err_tok);
          }
        }
        else 
        {
          Token err_tok;
          err_tok.type = TokenType::IDENTIFIER;
          err_tok.pos = pos;
          err_tok.lexemes = c;
          err(1, err_tok);
        }
      }
      if (curr != name_trie.getTrie())
      {
        Token tok;
        tok.type = TokenType::IDENTIFIER;
        tok.pos = pos;
        tok.lexemes = curr->lexemes;
        adjacent_nodes.push(std::make_unique<ValueNode>(tok));
      }
      Node* temp = node->parent;
      Node* node_to_replace = node;
      unique_ptr<Node> left_node;
      unique_ptr<Node> right_node;
      while (!adjacent_nodes.empty())
      {
        if (right_node == nullptr)
        {
          right_node = std::move(adjacent_nodes.top());
          adjacent_nodes.pop();
        }
        else if (temp->getType() == NodeType::UNARY_OPERATOR)
        {
          UnaOpNode* temp_una = static_cast<UnaOpNode*>(temp);
          left_node = std::move(adjacent_nodes.top());
          adjacent_nodes.pop();
          Token place_holder;
          place_holder.type = TokenType::ADJACENT;
          temp_una->node = std::make_unique<BinOpNode>(left_node, place_holder, right_node);
          temp = temp_una->node.get();
          if (!adjacent_nodes.empty())
          {
            node_to_replace = static_cast<BinOpNode*>(temp)->node_left.get();
            right_node = std::move(static_cast<BinOpNode*>(temp)->node_left);
          }
        }
        else if (temp->getType() == NodeType::BINARY_OPERATOR)
        {
          BinOpNode* temp_bin = static_cast<BinOpNode*>(temp); 
          left_node = std::move(adjacent_nodes.top());
          adjacent_nodes.pop();
          Token place_holder;
          place_holder.type = TokenType::ADJACENT;
          if (node_to_replace == temp_bin->node_left.get())
          {
            temp_bin->node_left = std::make_unique<BinOpNode>(left_node, place_holder, right_node);
            temp = temp_bin->node_left.get();
          }
          else
          {
            temp_bin->node_right = std::make_unique<BinOpNode>(left_node, place_holder, right_node);
            temp = temp_bin->node_right.get();
          }
          if (!adjacent_nodes.empty())
          {
            node_to_replace = static_cast<BinOpNode*>(temp)->node_left.get();
            right_node = std::move(static_cast<BinOpNode*>(temp)->node_left);
          }
        }
        else 
        {
          err(2, Token());
        }
      }
      if (right_node != nullptr)
      {
        if (temp->getType() == NodeType::UNARY_OPERATOR)
        {
          UnaOpNode* temp_una = static_cast<UnaOpNode*>(temp);
          temp_una->node = std::move(right_node);
        } 
        else if (temp->getType() == NodeType::BINARY_OPERATOR)
        {
          BinOpNode* temp_bin = static_cast<BinOpNode*>(temp);
          if (node_to_replace == temp_bin->node_left.get())
          {
            temp_bin->node_left = std::move(right_node);
          }
          else
          {
            temp_bin->node_right = std::move(right_node);
          }
        }
      }
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
  //this->parse_trees = parse_trees;
  for (int i = 0; i < parse_trees->size(); i++)
  {
    analyzeTree((*parse_trees)[i].get());
  }
}

void Definer::getSymbolTable()
{

}
