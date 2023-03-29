-- LexerTest.lua

require "script/global"
require "script/libs"

project "LexerTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/test/front/LexerTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/front"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util"),
    (wGL .. "/stem/inc/util/error")
  }

  useTokenLib()
  useErrorLib()
  useReaderLib()
  useLexerLib()

project "LexerTest"