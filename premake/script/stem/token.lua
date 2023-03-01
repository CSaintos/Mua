-- token.lua

require "script/global"

project "token"
  kind "SharedLib"
  language "C++"
  location "%{wks.location}/%{prj.name}"
  targetdir "%{wks.location}/../../build/%{wks.name}/%{prj.name}"
  objdir "%{wks.location}/../../bin/%{wks.name}/%{prj.name}"

  files {
    (globalLoc .. "/stem/src/util/token/*.cpp")
  }

  includedirs {
    (globalLoc .. "/stem/inc/util/token"),
    (globalLoc .. "/stem/inc/util")
  }

project "token"