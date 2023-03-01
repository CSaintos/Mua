-- error.lua

require "script/global"

project "error"
  kind "SharedLib"
  language "C++"
  location (prjLoc)
  targetdir (tarLoc)
  objdir (objLoc)

  files {
    (globalLoc .. "/stem/src/util/error/**.cpp")
  }

  includedirs {
    {globalLoc .. "/stem/inc/util/error"},
    {globalLoc .. "/stem/inc/util"}
  }

project "error"