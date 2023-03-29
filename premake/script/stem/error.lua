-- error.lua

require "script/global"

project "error"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/util/error/**.cpp")
  }

  includedirs {
    {wGL .. "/stem/inc/util/error"},
    {wGL .. "/stem/inc/util"}
  }

project "error"