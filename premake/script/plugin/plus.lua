-- plus.lua

require "script/global"

project "plus"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/plugin/algebra/Plus.cpp")
  }

  includedirs {
    (wGLoc .. "/plugin/algebra"),
    (wGLoc .. "/stem/inc/util"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**"),
    (wGLoc .. "/stem/api")
  }

  useTokenLib()
  useNodeLib()
project "plus"