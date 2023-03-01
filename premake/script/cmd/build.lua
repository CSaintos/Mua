-- build.lua

require "script/global"

do 
local stem_token

newaction {
  trigger = "build",
  description = "Build project (mingw32-make)",

  newoption {
    trigger = "stem",
    value = "project",
    description = "Build project",
    allowed = {
      {"token", "token lib"},
      {"all", "all stem projects"}
    }
  },

  onStart = function()
    if (_OPTIONS["stem"] == "token") then
      stem_token = true
    elseif (_OPTIONS["stem"] == "all") then
      stem_token = true
    end
  end,

  execute = function()
    if (stem_token) then
      print "Building token lib"
      os.chdir (tokenLoc)
      os.execute("mingw32-make")
    end
  end
}
end