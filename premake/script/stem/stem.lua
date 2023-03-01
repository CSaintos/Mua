-- stem.lua

workspace "stem"
  configurations { "Debug", "Release" }
  type { "Test", "Main" }
  location ("../../../make/stem")

  filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"
  
  filter { "configurations:Release" }
    defines { "RELEASE" }
    optimize "On"

  filter {}

  include "script/stem/token.lua"

workspace "stem"

