-- ParserTest.lua

require "script/global"
require "script/libs"

project "ParserTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/front/ParserTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/front"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util"),
    (wGLoc .. "/stem/inc/util/error"),
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**")
  }

  useTokenLib()
  useErrorLib()
  useNodeLib()
  useReaderLib()
  useLexerLib()
  useParserLib()

project "LexerTest"