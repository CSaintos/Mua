-- NodeTest.lua

require "script/global"
require "script/libs"

project "NodeTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/util/node/NodeTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util")
  }

  useNodeLib()
  useTokenLib()
project "NodeTest"