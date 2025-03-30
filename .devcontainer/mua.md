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

interface INodeFactory
INodeFactory ..> TokenType
INodeFactory ..> Token
INodeFactory ..> NodeType

struct Node
Node --> Token
Node --> INodeFactory
Node ..> NodeType
Node ..> InterpretType

INodeFactory ..> Node

struct ValueNode
ValueNode --|> Node
ValueNode ..> Token
ValueNode ..> NodeType
ValueNode ..> InterpretType
ValueNode ..> INodeFactory

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
NumberUtils ..> INodeFactory

class NodeUtils
NodeUtils ..> Node
NodeUtils ..> NodeType
NodeUtils ..> BinOpNode
NodeUtils ..> UnaOpNode

struct FSlash
FSlash --|> BinOpNode
FSlash ..> Token
FSlash ..> TokenType
FSlash ..> NodeType
FSlash ..> Node
FSlash ..> UnaOpNode
FSlash ..> NodeUtils
FSlash ..> NumberUtils
FSlash ..> InterpretType
FSlash ..> INodeFactory

struct UnaMinus
UnaMinus --|> UnaOpNode
UnaMinus ..> Token
UnaMinus ..> TokenType
UnaMinus ..> Node
UnaMinus ..> NodeUtils
UnaMinus ..> InterpretType
UnaMinus ..> INodeFactory

struct UnaPlus
UnaPlus --|> UnaOpNode
UnaPlus ..> Token
UnaPlus ..> TokenType
UnaPlus ..> Node
UnaPlus ..> NumberUtils
UnaPlus ..> NodeUtils
UnaPlus ..> InterpretType
UnaPlus ..> INodeFactory

struct Paren
Paren --|> UnaOpNode
Paren ..> TokenType
Paren ..> Token
Paren ..> Node
Paren ..> InterpretType
Paren ..> NodeUtils
Paren ..> INodeFactory

struct Let
Let --|> UnaOpNode
Let ..> Node
Let ..> Token
Let ..> InterpretType
Let ..> INodeFactory

struct Semicolon
Semicolon --|> UnaOpNode
Semicolon ..> Node
Semicolon ..> Token
Semicolon ..> InterpretType
Semicolon ..> INodeFactory

struct BinPlus
BinPlus --|> BinOpNode
BinPlus ..> Token
BinPlus ..> TokenType
BinPlus ..> Node
BinPlus ..> NodeType
BinPlus ..> FSlash
BinPlus ..> UnaOpNode
BinPlus ..> NodeUtils
BinPlus ..> NumberUtils
BinPlus ..> InterpretType
BinPlus ..> INodeFactory

struct BinMinus
BinMinus --|> BinOpNode
BinMinus ..> Token
BinMinus ..> TokenType
BinMinus ..> Node
BinMinus ..> FSlash
BinMinus ..> UnaOpNode
BinMinus ..> NodeUtils
BinMinus ..> NumberUtils
BinMinus ..> InterpretType
BinMinus ..> INodeFactory

struct Asterisk
Asterisk --|> BinOpNode
Asterisk ..> Token
Asterisk ..> TokenType
Asterisk ..> Node
Asterisk ..> UnaOpNode
Asterisk ..> NodeUtils
Asterisk ..> NumberUtils
Asterisk ..> InterpretType
Asterisk ..> INodeFactory

struct Percent
Percent --|> BinOpNode
Percent ..> Token
Percent ..> TokenType
Percent ..> Node
Percent ..> NumberUtils
Percent ..> NodeUtils
Percent ..> InterpretType
Percent ..> INodeFactory

struct Caret
Caret --|> BinOpNode
Caret ..> Token
Caret ..> TokenType
Caret ..> TokenUtils
Caret ..> Node
Caret ..> UnaOpNode
Caret ..> NodeUtils
Caret ..> NumberUtils
Caret ..> InterpretType
Caret ..> INodeFactory

struct Equal
Equal --|> BinOpNode
Equal ..> Token
Equal ..> Node
Equal ..> InterpretType
Equal ..> INodeFactory

class NodeFactory
NodeFactory ...|> INodeFactory
NodeFactory ...> TokenType
NodeFactory ...> TokenUtils
NodeFactory ...> Token
NodeFactory ...> NodeType
NodeFactory ...> Node
NodeFactory ...> ValueNode
NodeFactory ...> BinPlus
NodeFactory ...> UnaPlus
NodeFactory ...> UnaMinus
NodeFactory ...> BinMinus
NodeFactory ...> Asterisk
NodeFactory ...> FSlash
NodeFactory ...> Percent
NodeFactory ...> Caret
NodeFactory ...> Paren
NodeFactory ...> Equal
NodeFactory ...> Let
NodeFactory ...> Semicolon

class Parser
Parser o---> Token
Parser o---> TokenType
Parser o---> Node
Parser ---> UnaOpNode
Parser ---> BinOpNode
Parser ---> INodeFactory
Parser ...> NodeFactory
Parser ...> Error

class NameTrie
NameTrie --> TrieNode

class Definer
Definer o---> Node
Definer ---> NameTrie
Definer ---> TrieNode
Definer ---> Position
Definer ---> INodeFactory
Definer ...> NodeFactory
Definer ...> TokenType
Definer ...> Token
Definer ...> NodeType
Definer ...> BinOpNode
Definer ...> UnaOpNode
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
