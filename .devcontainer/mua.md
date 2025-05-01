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
CharacterStream ..> CharacterType

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

struct NodeMeta

interface INodeState
INodeState ..> InterpretType

struct Node
Node --> Token
Node --> NodeMeta
Node --> INodeState
Node ..> NodeType
Node ..> InterpretType

interface INodeFactory
INodeFactory ..> TokenType
INodeFactory ..> Token
INodeFactory ..> NodeType
INodeFactory .> Node

INodeState ..> Node
Node --> INodeFactory

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
BinOpNode ..> INodeFactory
BinOpNode ..> INodeState
BinOpNode ..> InterpretType

struct UnaOpNode
UnaOpNode --|> Node
UnaOpNode ..> NodeType
UnaOpNode ..> Token
UnaOpNode ..> TokenType
UnaOpNode ..> InterpretType
UnaOpNode ..> INodeFactory
UnaOpNode ..> INodeState

class NumberUtils
NumberUtils ..> Character
NumberUtils ..> CharacterType
NumberUtils ..> CharacterUtils
NumberUtils ..> Token
NumberUtils ..> TokenType
NumberUtils ..> Node
NumberUtils ..> INodeFactory

class NodeUtils
NodeUtils ..> Node
NodeUtils ..> NodeType
NodeUtils ..> BinOpNode
NodeUtils ..> UnaOpNode

abstract BinOpState
BinOpState ..|> INodeState
BinOpState --> BinOpNode
BinOpState --> Node
BinOpState --> INodeFactory
BinOpState --> Token
BinOpState ..> TokenType
BinOpState ..> TokenUtils
BinOpState ..> UnaOpNode
BinOpState ..> NumberUtils
BinOpState ..> InterpretType

abstract UnaOpState
UnaOpState ..|> INodeState
UnaOpState --> UnaOpNode
UnaOpState --> Node
UnaOpState --> INodeFactory
UnaOpState --> Token
UnaOpState ..> InterpretType

class FSlash
FSlash --|> BinOpState
FSlash ..> Token
FSlash ..> TokenType
FSlash ..> NodeType
FSlash ..> Node
FSlash ..> UnaOpNode
FSlash ..> BinOpNode
FSlash ..> NodeUtils
FSlash ..> NumberUtils
FSlash ..> InterpretType

class UnaMinus
UnaMinus --|> UnaOpState
UnaMinus ..> Token
UnaMinus ..> TokenType
UnaMinus ..> TokenUtils
UnaMinus ..> Node
UnaMinus ..> NodeUtils
UnaMinus ..> InterpretType
UnaMinus ..> UnaOpNode
UnaMinus ..> BinOpNode

class UnaPlus
UnaPlus --|> UnaOpState
UnaPlus ..> Token
UnaPlus ..> TokenType
UnaPlus ..> Node
UnaPlus ..> NumberUtils
UnaPlus ..> NodeUtils
UnaPlus ..> InterpretType

class Paren
Paren --|> UnaOpState
Paren ..> TokenType
Paren ..> Token
Paren ..> Node
Paren ..> InterpretType
Paren ..> NodeUtils

class Let
Let --|> UnaOpState
Let ..> Node
Let ..> Token
Let ..> InterpretType

class Semicolon
Semicolon --|> UnaOpState
Semicolon ..> Node
Semicolon ..> Token
Semicolon ..> TokenType
Semicolon ..> TokenUtils
Semicolon ..> InterpretType
Semicolon ..> UnaOpNode
Semicolon ..> BinOpNode

class BinPlus
BinPlus --|> BinOpState
BinPlus ..> Token
BinPlus ..> TokenType
BinPlus ..> Node
BinPlus ..> NodeType
BinPlus ..> UnaOpNode
BinPlus ..> BinOpNode
BinPlus ..> NodeUtils
BinPlus ..> NumberUtils
BinPlus ..> InterpretType

class BinMinus
BinMinus --|> BinOpState
BinMinus ..> Token
BinMinus ..> TokenType
BinMinus ..> Node
BinMinus ..> NodeType
BinMinus ..> UnaOpNode
BinMinus ..> BinOpNode
BinMinus ..> NodeUtils
BinMinus ..> InterpretType

class Asterisk
Asterisk --|> BinOpState
Asterisk ..> Token
Asterisk ..> TokenType
Asterisk ..> Node
Asterisk ..> NodeType
Asterisk ..> UnaOpNode
Asterisk ..> BinOpNode
Asterisk ..> NodeUtils
Asterisk ..> NumberUtils
Asterisk ..> InterpretType

class Percent
Percent --|> BinOpState
Percent ..> Token
Percent ..> TokenType
Percent ..> Node
Percent ..> NodeType
Percent ..> UnaOpNode
Percent ..> BinOpNode
Percent ..> NumberUtils
Percent ..> NodeUtils
Percent ..> InterpretType

class Caret
Caret --|> BinOpState
Caret ..> Token
Caret ..> TokenType
Caret ..> TokenUtils
Caret ..> Node
Caret ..> UnaOpNode
Caret ..> BinOpNode
Caret ..> NodeUtils
Caret ..> NumberUtils
Caret ..> InterpretType

class Equal
Equal --|> BinOpState
Equal ..> Token
Equal ..> Node
Equal ..> BinOpNode
Equal ..> InterpretType

class NodeFactory
NodeFactory ...|> INodeFactory
NodeFactory ...> TokenType
NodeFactory ...> TokenUtils
NodeFactory ...> Token
NodeFactory ...> NodeType
NodeFactory ...> Node
NodeFactory ...> ValueNode
NodeFactory ...> BinOpNode
NodeFactory ...> UnaOpNode
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

enum CmdArg
struct CmdData
class Cmd
Cmd --> CmdData
Cmd ..> CmdArg

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
Main ...> Cmd
Main ...> CmdData

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
