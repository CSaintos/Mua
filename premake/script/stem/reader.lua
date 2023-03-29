-- reader.lua

require "script/global"

project "reader"
  kind "SharedLib"
  language "C++"
  initPrjLocs()

  files {
    (wGL .. "/stem/src/front/Reader.cpp")
  }

  includedirs {
    (wGL .. "/stem/inc/front")
  }

project "reader"