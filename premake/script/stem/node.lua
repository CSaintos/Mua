-- node.lua

require "script/global"

project "node"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (globalLoc .. "/stem/src/util/node/**.cpp")
  }

  includedirs {
    (globalLoc .. "/stem/inc/util/node/**"),
    (globalLoc .. "/stem/inc/util/token"),
    (globalLoc .. "/stem/inc/util")
  }

project "node"