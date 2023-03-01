-- plugin.lua

workspace "plugin"
  configurations { "Debug", "Release" }
  location "../../../make/plugin"
  
  filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"
  
  filter { "configurations:Release" }
    defines { "RELEASE" }
    optimize "On"

  filter {}