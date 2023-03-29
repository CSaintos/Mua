-- plus.lua

require "script/global"

project "plus"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/plugin/algebra/Plus.cpp")
  }

  includedirs {
    (wGL .. "/plugin/algebra"),
    (wGL .. "/stem/inc/util"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/api")
  }

  useTokenLib()
  useNodeLib()
project "plus"