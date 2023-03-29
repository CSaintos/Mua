-- PLTest.lua

require "script/global"
require "script/libs"

project "PLTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/test/plugin/PLTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/plugin"),
    (wGL .. "/stem/api"),
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util")
  }

  usePLLib()

project "PLTest"