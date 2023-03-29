-- parser.lua

require "script/global"

project "parser"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/front/Parser.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/front"),
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util/error"),
    (wGL .. "/stem/inc/util")
  }

  useErrorLib()
  useTokenLib()
  useNodeLib()
project "parser"