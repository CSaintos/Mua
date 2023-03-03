-- global.lua

-- paths
globalLoc = ".."
makeLoc = globalLoc .. "/make"
  stemLoc = makeLoc .. "/stem"
    tokenLoc = stemLoc .. "/token"
    nodeLoc = stemLoc .. "/node"
    errorLoc = stemLoc .. "/error"
    readerLoc = stemLoc .. "/reader"
    PLLoc = stemLoc .. "/PL"
    lexerLoc = stemLoc .. "/lexer"
    parserLoc = stemLoc .. "/parser"
    generatorLoc = stemLoc .. "/generator"
  stemTestLoc = makeLoc .. "/stem-test"
    TokenUtilsTestLoc = stemTestLoc .. "/TokenUtilsTest"
    IllegalCharErrorTestLoc = stemTestLoc .. "/IllegalCharErrorTest"
    NodeTestLoc = stemTestLoc .. "/NodeTest"
    ReaderTestLoc = stemTestLoc .. "/ReaderTest"
    PLTestLoc = stemTestLoc .. "/PLTest"
    LexerTestLoc = stemTestLoc .. "/LexerTest"
    ParserTestLoc = stemTestLoc .. "/ParserTest"
    GeneratorTestLoc = stemTestLoc .. "/GeneratorTest"
  pluginLoc = makeLoc .. "/plugin"
buildLoc = globalLoc .. "/build"
binLoc = globalLoc .. "/bin"

-- workspace paths
wGLoc = "../../.."
wMLoc = (wGLoc .. "/make")

-- project paths
prjLoc = "%{wks.location}/%{prj.name}"
tarLoc = "%{wks.location}/../../build/%{wks.name}/%{prj.name}"
objLoc = "%{wks.location}/../../bin/%{wks.name}/%{prj.name}"

-- project functions
function initPrjLocs()
  location (prjLoc)
  targetdir (tarLoc)
  objdir (objLoc)
end