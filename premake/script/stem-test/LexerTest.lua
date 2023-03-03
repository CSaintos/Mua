-- LexerTest.lua

require "script/global"
require "script/libs"

project "LexerTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/front/LexerTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/front"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util"),
    (wGLoc .. "/stem/inc/util/error")
  }

  useTokenLib()
  useErrorLib()
  useReaderLib()
  useLexerLib()

project "LexerTest"