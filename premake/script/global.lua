-- global.lua

-- paths
globalLoc = ".."
makeLoc = globalLoc .. "/make"
  stemLoc = makeLoc .. "/stem"
    tokenLoc = stemLoc .. "/token"
    nodeLoc = stemLoc .. "/node"
    errorLoc = stemLoc .. "/error"
  pluginLoc = makeLoc .. "/plugin"
buildLoc = globalLoc .. "/build"
binLoc = globalLoc .. "/bin"

-- project paths
prjLoc = "%{wks.location}/%{prj.name}"
tarLoc = "%{wks.location}/../../build/%{wks.name}/%{prj.name}"
objLoc = "%{wks.location}/../../bin/%{wks.name}/%{prj.name}"