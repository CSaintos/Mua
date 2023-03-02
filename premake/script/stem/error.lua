-- error.lua

require "script/global"

project "error"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/src/util/error/**.cpp")
  }

  includedirs {
    {wGLoc .. "/stem/inc/util/error"},
    {wGLoc .. "/stem/inc/util"}
  }

project "error"