# Mua Class Diagram

```plantuml
@startuml mua class diagram
'https://plantuml.com/class-diagram
title mua class diagram

!pragma ratio 0.8
hide methods
hide fields

struct Position

enum CharacterType

class CharacterUtils
CharacterUtils o--> CharacterType

struct Character
Character --> CharacterType
Character --> Position
Character ..> CharacterUtils

class Error
Error --> Position

class CharacterStream
CharacterStream o--> Character
CharacterStream --> Position
CharacterStream ..> CharacterUtils
CharacterStream ..> Error

class Reader
Reader o--> Character
Reader --> Position
Reader --> CharacterStream

enum TokenType

class TokenUtils
TokenUtils o--> TokenType

struct Token
Token --> TokenType
Token --> Position
Token ..> TokenUtils

struct TrieNode
TrieNode o--> TrieNode
TrieNode --> TokenType

class TokenTrie
TokenTrie --> TrieNode
TokenTrie ..> TokenUtils
TokenTrie ..> TokenType

class Lexer
Lexer o--> Character
Lexer o--> Token
Lexer --> TokenTrie
Lexer --> TrieNode
Lexer ..> Error
Lexer ..> CharacterType
Lexer ..> TokenType

enum NodeType

enum InterpretType

struct Node
Node --> Token
Node ..> NodeType
Node ..> InterpretType

struct ValueNode
ValueNode --|> Node
ValueNode ..> Token
ValueNode ..> NodeType
ValueNode ..> InterpretType

struct BinOpNode
BinOpNode --|> Node
BinOpNode ..> Token
BinOpNode ..> TokenType
BinOpNode ..> NodeType
BinOpNode ..> InterpretType

struct UnaOpNode
UnaOpNode --|> Node
UnaOpNode ..> NodeType
UnaOpNode ..> Token
UnaOpNode ..> InterpretType

class NumberUtils
NumberUtils ..> Character
NumberUtils ..> CharacterType
NumberUtils ..> CharacterUtils
NumberUtils ..> Token
NumberUtils ..> TokenType
NumberUtils ..> Node
NumberUtils ..> ValueNode

class NodeUtils
NodeUtils ..> Node
NodeUtils ..> NodeType
NodeUtils ..> BinOpNode
NodeUtils ..> UnaOpNode

struct UnaMinus
UnaMinus --|> UnaOpNode
UnaMinus ..> Token
UnaMinus ..> TokenType
UnaMinus ..> Node
UnaMinus ..> NodeUtils
UnaMinus ..> InterpretType

struct UnaPlus
UnaPlus --|> UnaOpNode
UnaPlus ..> Token
UnaPlus ..> TokenType
UnaPlus ..> Node
UnaPlus ..> ValueNode
UnaPlus ..> NumberUtils
UnaPlus ..> NodeUtils
UnaPlus ..> InterpretType
UnaPlus ..> UnaMinus

struct Paren
Paren --|> UnaOpNode
Paren ..> Token
Paren ..> Node
Paren ..> InterpretType
Paren ..> NodeUtils

struct Let
Let --|> UnaOpNode
Let ..> Node
Let ..> Token
Let ..> InterpretType

struct Semicolon
Semicolon --|> UnaOpNode
Semicolon ..> Node
Semicolon ..> Token
Semicolon ..> InterpretType

struct BinPlus
BinPlus --|> BinOpNode
BinPlus ..> Token
BinPlus ..> TokenType
BinPlus ..> Node
BinPlus ..> ValueNode
BinPlus ..> UnaOpNode
BinPlus ..> UnaMinus
BinPlus ..> Paren
BinPlus ..> NodeUtils
BinPlus ..> NumberUtils
BinPlus ..> InterpretType

struct BinMinus
BinMinus --|> BinOpNode
BinMinus ..> Token
BinMinus ..> TokenType
BinMinus ..> Node
BinMinus ..> ValueNode
BinMinus ..> BinPlus
BinMinus ..> UnaOpNode
BinMinus ..> UnaMinus
BinMinus ..> NodeUtils
BinMinus ..> NumberUtils
BinMinus ..> InterpretType

BinPlus ..> BinMinus

struct Asterisk
Asterisk --|> BinOpNode
Asterisk ..> Token
Asterisk ..> TokenType
Asterisk ..> Node
Asterisk ..> ValueNode
Asterisk ..> UnaOpNode
Asterisk ..> UnaMinus
Asterisk ..> Paren
Asterisk ..> NodeUtils
Asterisk ..> NumberUtils
Asterisk ..> InterpretType

struct FSlash
FSlash --|> BinOpNode
FSlash ..> Token
FSlash ..> TokenType
FSlash ..> NodeType
FSlash ..> Node
FSlash ..> Asterisk
FSlash ..> UnaOpNode
FSlash ..> UnaMinus
FSlash ..> Paren
FSlash ..> ValueNode
FSlash ..> NodeUtils
FSlash ..> NumberUtils
FSlash ..> InterpretType

NumberUtils ..> FSlash
BinPlus ..> FSlash
BinMinus ..> FSlash
Asterisk ..> FSlash

struct Percent
Percent --|> BinOpNode
Percent ..> Token
Percent ..> TokenType
Percent ..> Node
Percent ..> ValueNode
Percent ..> NumberUtils
Percent ..> NodeUtils
Percent ..> InterpretType

struct Caret
Caret --|> BinOpNode
Caret ..> Token
Caret ..> TokenType
Caret ..> TokenUtils
Caret ..> Node
Caret ..> UnaOpNode
Caret ..> ValueNode
Caret ..> Paren
Caret ..> UnaMinus
Caret ..> Asterisk
Caret ..> FSlash
Caret ..> NodeUtils
Caret ..> NumberUtils
Caret ..> InterpretType

struct Equal
Equal --|> BinOpNode
Equal ..> Token
Equal ..> Node
Equal ..> InterpretType

class Parser
Parser o---> Token
Parser o---> TokenType
Parser o---> Node
Parser ---> UnaOpNode
Parser ---> BinOpNode
Parser ...> Error
Parser ...> UnaPlus
Parser ...> UnaMinus
Parser ...> Paren
Parser ...> Let
Parser ...> BinPlus
Parser ...> BinMinus
Parser ...> Asterisk
Parser ...> FSlash
Parser ...> Percent
Parser ...> Caret
Parser ...> Equal
Parser ...> ValueNode
Parser ...> Error

class NameTrie
NameTrie --> TrieNode

class Definer
Definer o---> Node
Definer ---> NameTrie
Definer ---> TrieNode
Definer ---> Position
Definer ...> TokenType
Definer ...> Token
Definer ...> NodeType
Definer ...> BinOpNode
Definer ...> UnaOpNode
Definer ...> Asterisk
Definer ...> ValueNode
Definer ...> Error

class Interpreter
Interpreter ...> Node
Interpreter ...> InterpretType

class Writer

class Main
Main ...> Reader
Main ...> Character
Main ...> CharacterStream
Main ...> Lexer
Main ...> Node
Main ...> Parser
Main ...> Definer
Main ...> Interpreter
Main ...> Writer

@enduml
```

```plantuml
class Asterisk
class FSlash
class NodeFactory
interface INodeFactory
class Parser

NodeFactory ..> Asterisk
NodeFactory ..> FSlash
Asterisk ..> INodeFactory
FSlash ..> INodeFactory
Parser ..> NodeFactory
Parser ..> INodeFactory
```
