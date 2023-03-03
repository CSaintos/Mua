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
  include "script/stem/reader.lua"
  include "script/stem/PL.lua"
  include "script/stem/lexer.lua"
  include "script/stem/parser.lua"

workspace "stem"

