-- token-test.lua

require "script/global"
require "script/libs"

project "TokenUtilsTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()
  -- runpathdirs { tL..TokenUtilsTL }
  -- flags {"RelativeLinks"}
  linkoptions { "-Wl,-rpath=$$(pwd)"}

  files {
    (wGL .. "/stem/test/util/token/TokenUtilsTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util")
  }

  useTokenLib()

project "TokenUtilsTest"