-- plugin.lua

require "script/global"

workspace "plugin"
  configurations { "Debug", "Release" }
  location (wML .. "/plugin")
  
  filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"
  
  filter { "configurations:Release" }
    defines { "RELEASE" }
    optimize "On"

  filter {}

  include "script/plugin/plus.lua"

workspace "plugin"