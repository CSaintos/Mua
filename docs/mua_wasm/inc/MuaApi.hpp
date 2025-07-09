#pragma once

#include <emscripten/bind.h>

#include <string>
#include <list>
#include <memory>
#include <sstream>

#include "Character.hpp"
#include "CharacterStream.hpp"
#include "Lexer.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Definer.hpp"
#include "Interpreter.hpp"

namespace mua
{
  class MuaApi
  {
  private:
    Lexer lexer;
    Parser parser;
    Definer definer;
    CharacterStream c_stream;
  public:
    MuaApi();

    std::string calculate(std::string input, bool is_debug);
  };
}

EMSCRIPTEN_BINDINGS(mua_module) {
  emscripten::class_<mua::MuaApi>("MuaApi")
  .constructor()
  .function("calculate", &mua::MuaApi::calculate)
  ;
}
