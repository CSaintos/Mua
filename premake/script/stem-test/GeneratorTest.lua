-- GeneratorTest.lua

require "script/global"
require "script/libs"

project "GeneratorTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/back/GeneratorTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/back"),
    (wGLoc .. "/stem/inc/front"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util"),
    (wGLoc .. "/stem/inc/util/error"),
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**"),
    (wGLoc .. "/stem/inc/plugin"),
    (wGLoc .. "/stem/api")
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