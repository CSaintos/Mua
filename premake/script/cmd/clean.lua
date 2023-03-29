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
      os.rmdir(mL .. stemL)
    elseif (_OPTIONS["make"] == "stemT") then
      print("Deleting " .. mL .. stemTL)
      os.rmdir(mL .. stemTL)
    elseif (_OPTIONS["make"] == "plugin") then
      print "Deleting /make/plugin"
      os.rmdir(mL .. pluginL)
    elseif (_OPTIONS["make"] == "all") then
      print "Deleting /make"
      os.rmdir(mL)
    elseif (_OPTIONS["build"] == "stem-token") then
      print "Deleting /build/stem/token"
      os.rmdir(tL .. tokenL)
    elseif (_OPTIONS["build"] == "stem-node") then
      print "Deleting /build/stem/node"
      os.rmdir(tL .. nodeL)
    elseif (_OPTIONS["build"] == "stem-error") then
      print "Deleting /build/stem/error"
      os.rmdir(tL .. errorL)
    elseif (_OPTIONS["build"] == "stem-reader") then
      print "Deleting /build/stem/reader"
      os.rmdir(tL .. readerL)
    elseif (_OPTIONS["build"] == "stem-PL") then
      print "Deleting /build/stem/PL"
      os.rmdir(tL .. PLL)
    elseif (_OPTIONS["build"] == "stem-lexer") then
      print "Deleting /build/stem/lexer"
      os.rmdir(tL .. lexerL)
    elseif (_OPTIONS["build"] == "stem-parser") then
      print "Deleting /build/stem/parser"
      os.rmdir(tL .. parserL)
    elseif (_OPTIONS["build"] == "stem-generator") then
      print "Deleting /build/stem/generator"
      os.rmdir(tL .. generatorL)
    elseif (_OPTIONS["build"] == "stem-all") then
      print "Deleting /build/stem"
      os.rmdir(tL .. stemL)
    elseif (_OPTIONS["build"] == "stemT-TokenUtils") then
      print "Deleting /build/stem-test/TokenUtilsTest"
      os.rmdir(tL .. TokenUtilsTL)
    elseif (_OPTIONS["build"] == "stemT-IllegalCharError") then
      print "Deleting /build/stem-test/IllegalCharErrorTest"
      os.rmdir(tL .. IllegalCharErrorTL)
    elseif (_OPTIONS["build"] == "stemT-Node") then
      print "Deleting /build/stem-test/NodeTest"
      os.rmdir(tL .. NodeTL)
    elseif (_OPTIONS["build"] == "stemT-Reader") then
      print "Deleting /build/stem-test/ReaderTest"
      os.rmdir(tL .. ReaderTL)
    elseif (_OPTIONS["build"] == "stemT-PL") then
      print "Deleting /build/stem-test/PLTest"
      os.rmdir(tL .. PLTL)
    elseif (_OPTIONS["build"] == "stemT-Lexer") then
      print "Deleting /build/stem-test/LexerTest"
      os.rmdir(tL .. LexerTL)
    elseif (_OPTIONS["build"] == "stemT-Parser") then
      print "Deleting /build/stem-test/ParserTest"
      os.rmdir(tL .. ParserTL)
    elseif (_OPTIONS["build"] == "stemT-Generator") then
      print "Deleting /build/stem-test/GeneratorTest"
      os.rmdir(tL .. GeneratorTL)
    elseif (_OPTIONS["build"] == "stemT-all") then
      print "Deleting /build/stem-test"
      os.rmdir(tL .. stemTL)
    elseif (_OPTIONS["build"] == "plugin-plus") then
      print "Deleting /build/plugin/plus"
      os.rmdir(tL .. plusL)
    elseif (_OPTIONS["build"] == "plugin-all") then
      print "Deleting /build/plugin"
      os.rmdir(tL .. pluginL)
    elseif (_OPTIONS["bin"]) then
      print "Deleting /bin"
      os.rmdir(bL)
    elseif (_OPTIONS["all"]) then
      print "Deleting make, build, and bin directories"
      os.rmdir(mL)
      os.rmdir(tL)
      os.rmdir(bL)
    end
  end
}