-- PLTest.lua

require "script/global"
require "script/libs"

project "PLTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/plugin/PLTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/plugin"),
    (wGLoc .. "/stem/api"),
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util")
  }

  usePLLib()

project "PLTest"