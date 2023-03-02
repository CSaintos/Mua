-- IllegalCharErrorTest.lua

require "script/global"
require "script/libs"

project "IllegalCharErrorTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/util/error/IllegalCharErrorTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/util/error"),
    (wGLoc .. "/stem/inc/util")
  }

  useErrorLib()

project "IllegalCharErrorTest"