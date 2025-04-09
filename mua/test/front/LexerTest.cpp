#include <string>
#include <iostream>

#include "Character.hpp"
#include "Token.hpp"

#include "Reader.hpp"
#include "Lexer.hpp"

using namespace std;
using namespace mua;

int main(int argc, char* argv[])
{
  // file name
  std::string file_name = argv[argc-1];

  // create reader with file name
  Reader reader(file_name);
  // create lexer with file name
  Lexer lexer;

  int line_length = 0;
  list<Character> *char_list = nullptr;
  list<Token> *token_stream = nullptr;
  list<Token>::iterator itr;
  // do ... while line_length isn't -1
  do {
    // Read the next line and get the length
    line_length = reader.readLine();
    // Print the length of the line
    // cout << "Line length: " << line_length << endl;
    // Get the character list from the reader as pointer.
    char_list = reader.getList();
    // lex the char list
    lexer.lex(char_list);
    // get token stream
    token_stream = lexer.getList();
    // Print the length of the token stream
    //~~std::cout << "TokenStream length: " << token_stream->size() << std::endl;
    // print token stream
    for (itr = token_stream->begin(); itr != token_stream->end(); ++itr)
    {
      cout << itr->to_string() << ", ";
    }
    cout << endl;
  } while(line_length != -1);

  return 0;
}
