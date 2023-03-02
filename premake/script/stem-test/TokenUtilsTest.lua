-- token-test.lua

require "script/global"
require "script/libs"

project "TokenUtilsTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/util/token/TokenUtilsTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util")
  }

  useTokenLib()

project "TokenUtilsTest"