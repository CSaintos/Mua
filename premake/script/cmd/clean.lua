-- clean.lua

require "script/global"

-- option vars
newaction {
  trigger = "clean",
  description = "Clean workspace (build) default",

  newoption {
    trigger = "make",
    value = "workspace",
    description = "Clean make files",
    allowed = {
      {"stem", "Main workspace"},
      {"plugin", "Plugin workspace"},
      {"all", "all workspaces"}
    }
  },

  newoption {
    trigger = "stem",
    value = "project",
    description = "Clean stem builds",
    allowed = {
      {"token", "token lib"},
      {"all", "all stem builds"}
    }
  },

  newoption {
    trigger = "bin",
    description = "Binaries"
  },

  newoption {
    trigger = "all",
    description = "All options"
  },

  execute = function()
    -- evaluates options
    if (_OPTIONS["make"] == "stem") then
      print "Deleting /make/stem"
      os.rmdir(stemLoc)
    elseif (_OPTIONS["make"] == "plugin") then
      print "Deleting /make/plugin"
      os.rmdir(pluginLoc)
    elseif (_OPTIONS["make"] == "all") then
      print "Deleting /make"
      os.rmdir(makeLoc)
    elseif (_OPTIONS["stem"] == "token") then
      print "Deleting /build/stem/token"
      os.rmdir(buildLoc .. "/stem/token")
    elseif (_OPTIONS["stem"] == "all") then
      print "Deleting /build/stem"
      os.rmdir(buildLoc .. "/stem")
    elseif (_OPTIONS["bin"]) then
      print "Deleting /bin"
      os.rmdir(binLoc)
    elseif (_OPTIONS["all"]) then
      print "Deleting make, build, and bin directories"
      os.rmdir(makeLoc)
      os.rmdir(buildLoc)
      os.rmdir(binLoc)
    end
  end
}