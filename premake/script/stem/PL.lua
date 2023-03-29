-- PL.lua

require "script/global"

project "PL"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/plugin/PluginLoader.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/plugin"),
    (wGL .. "/stem/api"),
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util")
  }

project "PL"