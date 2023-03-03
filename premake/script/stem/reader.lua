-- reader.lua

require "script/global"

project "reader"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/src/front/Reader.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/front")
  }

project "reader"