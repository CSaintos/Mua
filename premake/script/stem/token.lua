-- token.lua

require "script/global"

project "token"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/util/token/**.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util")
  }

project "token"