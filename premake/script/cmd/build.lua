-- build.lua

require "script/global"

function makeBuild(path)
  os.chdir(path)
  os.execute("mingw32-make")
end

newaction {
  trigger = "build",
  description = "Build project (mingw32-make)",

  newoption {
    trigger = "stem",
    value = "project",
    description = "Build project",
    allowed = {
      {"token", "token lib"},
      {"node", "node lib"},
      {"error", "error lib"},
      {"all", "all stem projects"}
    }
  },

  execute = function()
    if (_OPTIONS["stem"] == "token") then
      print "Building token lib"
      makeBuild(tokenLoc)
    elseif (_OPTIONS["stem"] == "node") then
      print "Building node lib"
      makeBuild(nodeLoc)
    elseif (_OPTIONS["stem"] == "error") then
      print "Building error lib"
      makeBuild(errorLoc)
    elseif (_OPTIONS["stem"] == "all") then
      print "Building stem project and libs"
      makeBuild(stemLoc)
    end
  end
}