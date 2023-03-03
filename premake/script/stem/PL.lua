-- PL.lua

require "script/global"

project "PL"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGLoc .. "/stem/src/plugin/PluginLoader.cpp")
  }

  includedirs {
    (wGLoc .. "/stem/inc/plugin"),
    (wGLoc .. "/stem/api"),
    (wGLoc .. "/stem/inc/util/node"),
    (wGLoc .. "/stem/inc/util/node/**"),
    (wGLoc .. "/stem/inc/util/token"),
    (wGLoc .. "/stem/inc/util")
  }

project "PL"