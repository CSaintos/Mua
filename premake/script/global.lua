-- global.lua

-- OS specific vars
if os.host() == "windows" then
  makeCmd = "mingw32-make"
  so = ".dll"
else
  makeCmd = "make"
  so = ".so"
end

-- paths
gL = ".."
mL = gL .. "/make"
tL = gL .. "/build"
bL = gL .. "/bin"

stemL = "/stem"
  tokenL = stemL .. "/token"
  nodeL = stemL .. "/node"
  errorL = stemL .. "/error"
  readerL = stemL .. "/reader"
  PLL = stemL .. "/PL"
  lexerL = stemL .. "/lexer"
  parserL = stemL .. "/parser"
  generatorL = stemL .. "/generator"
stemTL = "/stem-test"
  TokenUtilsTL = stemTL .. "/TokenUtilsTest"
  IllegalCharErrorTL = stemTL .. "/IllegalCharErrorTest"
  NodeTL = stemTL .. "/NodeTest"
  ReaderTL = stemTL .. "/ReaderTest"
  PLTL = stemTL .. "/PLTest"
  LexerTL = stemTL .. "/LexerTest"
  ParserTL = stemTL .. "/ParserTest"
  GeneratorTL = stemTL .. "/GeneratorTest"
pluginL = "/plugin"
  plusL = pluginL .. "/plus"

-- workspace paths
wGL = "../../.."
wML = (wGL .. "/make")

-- project paths
prjL = "%{wks.location}/%{prj.name}"
tarL = "%{wks.location}/../../build/%{wks.name}/%{prj.name}"
objL = "%{wks.location}/../../bin/%{wks.name}/%{prj.name}"

-- project functions
function initPrjLocs()
  location (prjL)
  targetdir (tarL)
  objdir (objL)
end

-- build functions
function copySO(fromDir, toDir, fileName)
  os.execute("{COPYFILE} "..tL..fromDir..fileName..so.." "..tL..toDir)
end