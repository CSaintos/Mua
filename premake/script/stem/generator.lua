-- generator.lua

require "script/global"

project "generator"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/back/Generator.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/back"),
    (wGL .. "/stem/inc/util/node"),
    (wGL .. "/stem/inc/util/node/**"),
    (wGL .. "/stem/inc/util/token"),
    (wGL .. "/stem/inc/util"),
    (wGL .. "/stem/api")
  }

  useNodeLib()
project "generator"