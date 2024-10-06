# Stem Class Diagram

```plantuml
@startuml stem class diagram
'https://plantuml.com/class-diagram
title newstem class diagram

!pragma ratio 0.7
hide methods

struct Position {
string file_name
int column_nums[2]
int line_num
void init()
}
enum CharacterType
class CharacterUtils {
+{static} unordered_map<char, CharacterType> cC_map
+{static} unordered_map<ChatacterType, string> repr_map
}
CharacterUtils o--> CharacterType
struct Character {
CharacterType type
Position pos
char character
}
Character --> CharacterType
Character --> Position
class Reader {
fstream file
list<Character> char_list
Position pos
string file_name
string line
}
Reader o--> Character
Reader --> Position
Reader ..> CharacterUtils
Reader ..> Error
Reader ..> CharacterType
enum TokenType
struct Token {
TokenType type
Position pos
string lexemes
}
Token --> TokenType
Token --> Position
Token ..> TokenUtils
class TokenUtils {
+{static} unordered_map<TokenType, string> m_TS_map
+{static} unordered_map<string, TokenType> m_RT_map
}
TokenUtils o--> TokenType
class Error {
-stringstream ss
#Position pos
#string err_name
#string details
}
Error --> Position
class TrieNode {
unordered_map<char, TrieNode> nodes
TokenType type
string lexemes
}
TrieNode o--> TrieNode
TrieNode --> TokenType
class TokenTrie {
-{static} TokenTrie instance
-Trienode root
-{static} bool isInstanciated
}
TokenTrie --> TrieNode
TokenTrie ..> TokenUtils
class Lexer {
list<Character> ls
list<Token> token_stream
list<Character> *char_list
list<Character>::iterator itr
list<Character>::iterator end
TokenTrie* token_trie
TrieNode* curr
Token token_temp
int dot_count
}
Lexer ..> Error
Lexer o--> Token
Lexer o--> Character
Lexer ..> CharacterType
Lexer ..> Position
Lexer ..> TokenType
Lexer ..> TokenUtils
Lexer --> TrieNode
Lexer --> TokenTrie
enum NodeType
struct Node {
Node* parent
Token token
}
Node --> Token
Node ..> NodeType
struct ValueNode
ValueNode --|> Node
ValueNode ..> Token
ValueNode ..> NodeType
struct BinOpNode {
unique_ptr<Node> node_left
unique_ptr<Node> node_right
}
BinOpNode --|> Node
BinOpNode ..> TokenType
BinOpNode ..> NodeType
BinOpNode ..> Token
struct UnaOpNode {
unique_ptr<Node> node
}
UnaOpNode --|> Node
UnaOpNode ..> NodeType
UnaOpNode ..> Token
UnaOpNode ..> TokenType
class Parser {
vector<unique_ptr<Node>> parse_trees
stack<unique_ptr<Node>> node_stack
queue<Node*> node_queue
list<Token>* token_stream
list<Token>::iterator itr
unique_ptr<Node> curr_node
unique_ptr<Node> left_node
unique_ptr<Node> right_node
unique_ptr<Node> op_node
TokenType last_type
TokenType last_op
UnaOpNode* unaop_node
int paren_count
bool let_stmt
bool right_paren
bool end_of_expr
bool end_of_stmt
}
Parser o---> Node
Parser o---> Token
Parser ---> "2" TokenType
Parser ---> UnaOpNode
Parser ...> Error
Parser ...> BinOpNode
Parser ...> ValueNode
Parser ...> Error

class NameTrie {
TrieNode root
}
NameTrie --> TrieNode
class Definer {
stack<Node*> analyze_nodes
unordered_map<string, Node*> name_table
stack<unique_ptr<Node>> adjacent_nodes
NameTrie name_trie
TrieNode* curr
Position pos
bool let_stmt
}
Definer o---> Node
Definer ---> NameTrie
Definer ---> TrieNode
Definer ---> Position
Definer ...> NodeType
Definer ...> BinOpNode
Definer ...> UnaOpNode
Definer ...> ValueNode
Definer ...> TokenType
Definer ...> Error
class Interpreter {
vector<unique_ptr<Node>>* parse_trees
}
Interpreter o---> Node
struct UnaPlus
UnaPlus --|> UnaOpNode
struct UnaMinus
UnaMinus --|> UnaOpNode
struct LParen
LParen --|> UnaOpNode
struct Semicolon
Semicolon --|> UnaOpNode
Semicolon ..> Token
Semicolon ..> Node
struct Let
Let --|> UnaOpNode
struct BinPlus
BinPlus --|> BinOpNode
BinPlus ..> Token
BinPlus ..> TokenType
BinPlus ..> Node
BinPlus ..> ValueNode
BinPlus ..> NodeUtils
BinPlus ..> NumberUtils
struct BinMinus
BinMinus --|> BinOpNode
BinMinus ..> Token
BinMinus ..> TokenType
BinMinus ..> Node
BinMinus ..> ValueNode
BinMinus ..> NodeUtils
BinMinus ..> NumberUtils
struct Asterisk
Asterisk --|> BinOpNode
Asterisk ..> Token
Asterisk ..> TokenType
Asterisk ..> Node
Asterisk ..> ValueNode
Asterisk ..> NodeUtils
Asterisk ..> NumberUtils
struct Adjacent
Adjacent --|> BinOpNode
struct FSlash
FSlash --|> BinOpNode
struct Percent
Percent --|> BinOpNode
struct Caret
Caret --|> BinOpNode
Caret ..> Token
Caret ..> TokenType
Caret ..> Node
Caret ..> ValueNode
Caret ..> NodeUtils
Caret ..> NumberUtils
struct Equal
Equal --|> BinOpNode
class NodeUtils
NodeUtils ..> Node
NodeUtils ..> NodeType
NodeUtils ..> BinOpNode
NodeUtils ..> UnaOpNode
class NumberUtils
NumberUtils ..> Character
NumberUtils ..> CharacterType
NumberUtils ..> CharacterUtils
Parser ...> Semicolon
Parser ...> BinPlus
Parser ...> BinMinus
Parser ...> Asterisk
Parser ...> Caret

@enduml
```
