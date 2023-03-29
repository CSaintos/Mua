-- ReaderTest.lua

require "script/global"
require "script/libs"

project "ReaderTest"
  kind "ConsoleApp"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/test/front/ReaderTest.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/front")
  }

  useReaderLib()

project "ReaderTest"