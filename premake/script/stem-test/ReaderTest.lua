-- ReaderTest.lua

require "script/global"
require "script/libs"

project "ReaderTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/test/front/ReaderTest.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/front")
  }

  useReaderLib()

project "ReaderTest"