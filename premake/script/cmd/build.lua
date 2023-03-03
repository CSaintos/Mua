-- build.lua

require "script/global"

function makeBuild(path)
  local cwd = os.getcwd()
  os.chdir(path)
  os.execute("mingw32-make")
  os.chdir(cwd)
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
      {"reader", "reader lib"},
      {"PL", "PL Lib"},
      {"lexer", "lexer lib"},
      {"parser", "parser lib"},
      {"generator", "generator lib"},
      {"all", "all stem projects"}
    }
  },

  newoption {
    trigger = "stem-test",
    value = "test project",
    description = "Build test project",
    allowed = {
      {"TokenUtils", "TokenUtilsTest.cpp"},
      {"IllegalCharError", "IllegalCharErrorTest.cpp"},
      {"Node", "NodeTest.cpp"},
      {"Reader", "ReaderTest.cpp"},
      {"PL", "PLTest.cpp"},
      {"Lexer", "LexerTest.cpp"},
      {"Parser", "ParserTest.cpp"},
      {"Generator", "GeneratorTest.cpp"},
      {"all", "all stem test projects"}
    }
  },

  newoption {
    trigger = "plugin",
    value = "plugin project",
    description = "Build plugin project",
    allowed = {
      {"plus", "plus lib"},
      {"all", "all plugin libs"}
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
    elseif (_OPTIONS["stem"] == "reader") then
      print "Building reader lib"
      makeBuild(readerLoc)
    elseif (_OPTIONS["stem"] == "PL") then
      print "Building PL lib"
      makeBuild(PLLoc)
    elseif (_OPTIONS["stem"] == "lexer") then
      print "Building lexer lib"
      makeBuild(lexerLoc)
    elseif (_OPTIONS["stem"] == "parser") then
      print "Building parser lib"
      makeBuild(parserLoc)
    elseif (_OPTIONS["stem"] == "generator") then
      print "Building generator lib"
      makeBuild(generatorLoc)
    elseif (_OPTIONS["stem"] == "all") then
      print "Building stem project and libs"
      makeBuild(stemLoc)
    elseif (_OPTIONS["stem-test"] == "TokenUtils") then
      print "Building TokenUtilsTest"
      makeBuild(TokenUtilsTestLoc)
      os.execute("{COPYFILE} ../build/stem/token/token.dll ../build/stem-test/TokenUtilsTest")
    elseif (_OPTIONS["stem-test"] == "IllegalCharError") then
      print "Building IllegalCharErrorTest"
      makeBuild(IllegalCharErrorTestLoc)
      os.execute("{COPYFILE} ../build/stem/error/error.dll ../build/stem-test/IllegalCharErrorTest")
    elseif (_OPTIONS["stem-test"] == "Node") then
      print "Building NodeTest"
      makeBuild(NodeTestLoc)
      os.execute("{COPYFILE} ../build/stem/node/node.dll ../build/stem-test/NodeTest")
      os.execute("{COPYFILE} ../build/stem/token/token.dll ../build/stem-test/NodeTest")
    elseif (_OPTIONS["stem-test"] == "Reader") then
      print "Building ReaderTest"
      makeBuild(ReaderTestLoc)
      os.execute("{COPYFILE} ../build/stem/reader/reader.dll ../build/stem-test/ReaderTest")
    elseif (_OPTIONS["stem-test"] == "Lexer") then
      print "Building LexerTest"
      makeBuild(LexerTestLoc)
      os.execute("{COPYFILE} ../build/stem/lexer/lexer.dll ../build/stem-test/LexerTest")
      os.execute("{COPYFILE} ../build/stem/reader/reader.dll ../build/stem-test/LexerTest")
      os.execute("{COPYFILE} ../build/stem/token/token.dll ../build/stem-test/LexerTest")
      os.execute("{COPYFILE} ../build/stem/error/error.dll ../build/stem-test/LexerTest")
    elseif (_OPTIONS["stem-test"] == "Parser") then
      print "Building ParserTest"
      makeBuild(ParserTestLoc)
      os.execute("{COPYFILE} ../build/stem/parser/parser.dll ../build/stem-test/ParserTest")
      os.execute("{COPYFILE} ../build/stem/lexer/lexer.dll ../build/stem-test/ParserTest")
      os.execute("{COPYFILE} ../build/stem/reader/reader.dll ../build/stem-test/ParserTest")
      os.execute("{COPYFILE} ../build/stem/token/token.dll ../build/stem-test/ParserTest")
      os.execute("{COPYFILE} ../build/stem/error/error.dll ../build/stem-test/ParserTest")
      os.execute("{COPYFILE} ../build/stem/node/node.dll ../build/stem-test/ParserTest")
    elseif (_OPTIONS["stem-test"] == "PL") then
      print "Building PLTest"
      makeBuild(PLTestLoc)
      os.execute("{COPYFILE} ../build/stem/PL/PL.dll ../build/stem-test/PLTest")
    elseif (_OPTIONS["stem-test"] == "Generator") then
      print "Building GeneratorTest"
      makeBuild(GeneratorTestLoc)
      os.execute("{COPYFILE} ../build/stem/generator/generator.dll ../build/stem-test/GeneratorTest")
      os.execute("{COPYFILE} ../build/stem/parser/parser.dll ../build/stem-test/GeneratorTest")
      os.execute("{COPYFILE} ../build/stem/lexer/lexer.dll ../build/stem-test/GeneratorTest")
      os.execute("{COPYFILE} ../build/stem/reader/reader.dll ../build/stem-test/GeneratorTest")
      os.execute("{COPYFILE} ../build/stem/token/token.dll ../build/stem-test/GeneratorTest")
      os.execute("{COPYFILE} ../build/stem/error/error.dll ../build/stem-test/GeneratorTest")
      os.execute("{COPYFILE} ../build/stem/node/node.dll ../build/stem-test/GeneratorTest")
      os.execute("{COPYFILE} ../build/stem/PL/PL.dll ../build/stem-test/GeneratorTest")
      print(os.mkdir("../build/stem-test/GeneratorTest/plugin"))
    elseif (_OPTIONS["plugin"] == "plus") then
      print "Building plus lib"
      makeBuild(plusLoc)
      os.execute("{COPYFILE} ../build/plugin/plus/plus.dll ../build/stem-test/GeneratorTest/plugin")
    end
  end
}