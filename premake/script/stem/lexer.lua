-- lexer.lua

require "script/global"

project "lexer"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/src/front/Lexer.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/front"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util"),
    (wGLoc .. "/stem/inc/util/error")
  }

  useErrorLib()
  useTokenLib()
project "lexer"