-- stem.lua

require "script/global"

workspace "stem"
  configurations { "Debug", "Release" }
  location (wMLoc .. "/stem")

  filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"
  
  filter { "configurations:Release" }
    defines { "RELEASE" }
    optimize "On"

  filter {}

  include "script/stem/token.lua"
  include "script/stem/node.lua"
  include "script/stem/error.lua"

workspace "stem"

