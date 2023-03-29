-- ParserTest.lua

require "script/global"
require "script/libs"

project "ParserTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/test/front/ParserTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/front"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util"),
    (wGL .. "/stem/inc/util/error"),
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**")
  }

  useTokenLib()
  useErrorLib()
  useNodeLib()
  useReaderLib()
  useLexerLib()
  useParserLib()

project "ParserTest"