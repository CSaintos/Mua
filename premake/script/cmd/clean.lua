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
      {"stemT", "Test workspace"},
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
      {"stem-generator", "stem: generator lib"},
      {"stem-all", "stem: all stem builds"},
      {"stemT-TokenUtils", "stemT: TokenUtils"},
      {"stemT-IllegalCharError", "stemT: IllegalCharError"},
      {"stemT-Node", "stemT: Node"},
      {"stemT-Reader", "stemT: Reader"},
      {"stemT-PL", "stemT: PL"},
      {"stemT-Lexer", "stemT: Lexer"},
      {"stemT-Parser", "stemT: Parser"},
      {"stemT-Generator", "stemT: Generator"},
      {"stemT-all", "stemT: all stem test builds"},
      {"plugin-plus", "plugin: plus lib"},
      {"plugin-all", "plugin: all plugin buils"}
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
      os.rmdir(makeLoc .. stemLoc)
    elseif (_OPTIONS["make"] == "stemT") then
      print("Deleting " .. makeLoc .. stemTestLoc)
      os.rmdir(makeLoc .. stemTestLoc)
    elseif (_OPTIONS["make"] == "plugin") then
      print "Deleting /make/plugin"
      os.rmdir(makeLoc .. pluginLoc)
    elseif (_OPTIONS["make"] == "all") then
      print "Deleting /make"
      os.rmdir(makeLoc)
    elseif (_OPTIONS["build"] == "stem-token") then
      print "Deleting /build/stem/token"
      os.rmdir(buildLoc .. tokenLoc)
    elseif (_OPTIONS["build"] == "stem-node") then
      print "Deleting /build/stem/node"
      os.rmdir(buildLoc .. nodeLoc)
    elseif (_OPTIONS["build"] == "stem-error") then
      print "Deleting /build/stem/error"
      os.rmdir(buildLoc .. nodeLoc)
    elseif (_OPTIONS["build"] == "stem-reader") then
      print "Deleting /build/stem/reader"
      os.rmdir(buildLoc .. readerLoc)
    elseif (_OPTIONS["build"] == "stem-PL") then
      print "Deleting /build/stem/PL"
      os.rmdir(buildLoc .. PLLoc)
    elseif (_OPTIONS["build"] == "stem-lexer") then
      print "Deleting /build/stem/lexer"
      os.rmdir(buildLoc .. lexerLoc)
    elseif (_OPTIONS["build"] == "stem-parser") then
      print "Deleting /build/stem/parser"
      os.rmdir(buildLoc .. parserLoc)
    elseif (_OPTIONS["build"] == "stem-generator") then
      print "Deleting /build/stem/generator"
      os.rmdir(buildLoc .. generatorLoc)
    elseif (_OPTIONS["build"] == "stem-all") then
      print "Deleting /build/stem"
      os.rmdir(buildLoc .. stemLoc)
    elseif (_OPTIONS["build"] == "stemT-TokenUtils") then
      print "Deleting /build/stem-test/TokenUtilsTest"
      os.rmdir(buildLoc .. TokenUtilsTestLoc)
    elseif (_OPTIONS["build"] == "stemT-IllegalCharError") then
      print "Deleting /build/stem-test/IllegalCharErrorTest"
      os.rmdir(buildLoc .. IllegalCharErrorTestLoc)
    elseif (_OPTIONS["build"] == "stemT-Node") then
      print "Deleting /build/stem-test/NodeTest"
      os.rmdir(buildLoc .. NodeTestLoc)
    elseif (_OPTIONS["build"] == "stemT-Reader") then
      print "Deleting /build/stem-test/ReaderTest"
      os.rmdir(buildLoc .. ReaderTestLoc)
    elseif (_OPTIONS["build"] == "stemT-PL") then
      print "Deleting /build/stem-test/PLTest"
      os.rmdir(buildLoc .. PLTestLoc)
    elseif (_OPTIONS["build"] == "stemT-Lexer") then
      print "Deleting /build/stem-test/LexerTest"
      os.rmdir(buildLoc .. LexerTestLoc)
    elseif (_OPTIONS["build"] == "stemT-Parser") then
      print "Deleting /build/stem-test/ParserTest"
      os.rmdir(buildLoc .. ParserTestLoc)
    elseif (_OPTIONS["build"] == "stemT-Generator") then
      print "Deleting /build/stem-test/GeneratorTest"
      os.rmdir(buildLoc .. GeneratorTestLoc)
    elseif (_OPTIONS["build"] == "stemT-all") then
      print "Deleting /build/stem-test"
      os.rmdir(buildLoc .. stemTestLoc)
    elseif (_OPTIONS["build"] == "plugin-plus") then
      print "Deleting /build/plugin/plus"
      os.rmdir(buildLoc .. plusLoc)
    elseif (_OPTIONS["build"] == "plugin-all") then
      print "Deleting /build/plugin"
      os.rmdir(buildLoc .. pluginLoc)
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