-- GeneratorTest.lua

require "script/global"
require "script/libs"

project "GeneratorTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/test/back/GeneratorTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/back"),
    (wGL .. "/stem/inc/front"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util"),
    (wGL .. "/stem/inc/util/error"),
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/inc/plugin"),
    (wGL .. "/stem/api")
  }

  useTokenLib()
  useErrorLib()
  useNodeLib()
  useReaderLib()
  useLexerLib()
  useParserLib()
  useGeneratorLib()
  usePLLib()

project "GeneratorTest"