-- IllegalCharErrorTest.lua

require "script/global"
require "script/libs"

project "IllegalCharErrorTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/test/util/error/IllegalCharErrorTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/util/error"),
    (wGL .. "/stem/inc/util")
  }

  useErrorLib()

project "IllegalCharErrorTest"