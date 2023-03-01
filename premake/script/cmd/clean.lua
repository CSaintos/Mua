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
    trigger = "build",
    value = "project",
    description = "Clean build(s)",
    allowed = {
      {"stem-token", "stem: token lib"},
      {"stem-node", "stem: node lib"},
      {"stem-error", "stem: error lib"},
      {"stem-all", "stem: all stem builds"}
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
    elseif (_OPTIONS["build"] == "stem-token") then
      print "Deleting /build/stem/token"
      os.rmdir(buildLoc .. "/stem/token")
    elseif (_OPTIONS["build"] == "stem-node") then
      print "Deleting /build/stem/node"
      os.rmdir(buildLoc .. "/stem/node")
    elseif (_OPTIONS["build"] == "stem-error") then
      print "Deleting /build/stem/error"
      os.rmdir(buildLoc .. "/stem/error")
    elseif (_OPTIONS["build"] == "stem-all") then
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