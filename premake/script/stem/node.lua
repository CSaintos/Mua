-- node.lua

require "script/global"
require "script/libs"

project "node"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/util/node/**.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util")
  }

  useTokenLib()

project "node"