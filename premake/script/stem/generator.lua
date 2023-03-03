-- generator.lua

require "script/global"

project "generator"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/src/back/Generator.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/back"),
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util"),
    (wGLoc .. "/stem/api")
  }

  useNodeLib()
project "generator"