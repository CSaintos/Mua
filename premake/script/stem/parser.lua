-- parser.lua

require "script/global"

project "parser"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/src/front/Parser.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/front"),
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util/error"),
    (wGLoc .. "/stem/inc/util")
  }

  useErrorLib()
  useTokenLib()
  useNodeLib()
project "parser"