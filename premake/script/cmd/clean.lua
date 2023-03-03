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
      {"stem-reader", "stem: reader lib"},
      {"stem-PL", "stem: PL lib"},
      {"stem-lexer", "stem: lexer lib"},
      {"stem-parser", "stem: parser lib"},
      {"stem-all", "stem: all stem builds"},
      {"stem-test-TokenUtils", "stem-test: TokenUtils"},
      {"stem-test-IllegalCharError", "stem-test: IllegalCharError"},
      {"stem-test-Node", "stem-test: Node"},
      {"stem-test-Reader", "stem-test: Reader"},
      {"stem-test-PL", "stem-test: PL"},
      {"stem-test-Lexer", "stem-test: Lexer"},
      {"stem-test-Parser", "stem-test: Parser"},
      {"stem-test-all", "stem-test: all stem test builds"}
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
    elseif (_OPTIONS["build"] == "stem-reader") then
      print "Deleting /build/stem/reader"
      os.rmdir(buildLoc .. "/stem/reader")
    elseif (_OPTIONS["build"] == "stem-PL") then
      print "Deleting /build/stem/PL"
      os.rmdir(buildLoc .. "/stem/PL")
    elseif (_OPTIONS["build"] == "stem-lexer") then
      print "Deleting /build/stem/lexer"
      os.rmdir(buildLoc .. "/stem/lexer")
    elseif (_OPTIONS["build"] == "stem-parser") then
      print "Deleting /build/stem/parser"
      os.rmdir(buildLoc .. "/stem/parser")
    elseif (_OPTIONS["build"] == "stem-all") then
      print "Deleting /build/stem"
      os.rmdir(buildLoc .. "/stem")
    elseif (_OPTIONS["build"] == "stem-test-TokenUtils") then
      print "Deleting /build/stem-test/TokenUtilsTest"
      os.rmdir(buildLoc .. "/stem-test/TokenUtilsTest")
    elseif (_OPTIONS["build"] == "stem-test-IllegalCharError") then
      print "Deleting /build/stem-test/IllegalCharErrorTest"
      os.rmdir(buildLoc .. "/stem-test/IllegalCharErrorTest")
    elseif (_OPTIONS["build"] == "stem-test-Node") then
      print "Deleting /build/stem-test/NodeTest"
      os.rmdir(buildLoc .. "/stem-test/NodeTest")
    elseif (_OPTIONS["build"] == "stem-test-Reader") then
      print "Deleting /build/stem-test/ReaderTest"
      os.rmdir(buildLoc .. "/stem-test/ReaderTest")
    elseif (_OPTIONS["build"] == "stem-test-PL") then
      print "Deleting /build/stem-test/PLTest"
      os.rmdir(buildLoc .. "/stem-test/PLTest")
    elseif (_OPTIONS["build"] == "stem-test-Lexer") then
      print "Deleting /build/stem-test/LexerTest"
      os.rmdir(buildLoc .. "/stem-test/LexerTest")
    elseif (_OPTIONS["build"] == "stem-test-Parser") then
      print "Deleting /build/stem-test/ParserTest"
      os.rmdir(buildLoc .. "/stem-test/ParserTest")
    elseif (_OPTIONS["build"] == "stem-test-all") then
      print "Deleting /build/stem-test"
      os.rmdir(buildLoc .. "/stem-test")
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