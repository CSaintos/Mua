-- NodeTest.lua

require "script/global"
require "script/libs"

project "NodeTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/test/util/node/NodeTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util")
  }

  useNodeLib()
  useTokenLib()
project "NodeTest"