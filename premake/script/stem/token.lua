-- token.lua

require "script/global"

project "token"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/src/util/token/**.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util")
  }

project "token"