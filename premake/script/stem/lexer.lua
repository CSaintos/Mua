-- lexer.lua

require "script/global"

project "lexer"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/front/Lexer.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/front"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util"),
    (wGL .. "/stem/inc/util/error")
  }

  useErrorLib()
  useTokenLib()
project "lexer"