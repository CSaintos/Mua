-- test-stem.lua

require "script/global"

workspace "stem-test"
  configurations { "Debug", "Release" }
  location (wMLoc .. "/stem-test")

  filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"
  filter { "configurations:Release" }
    defines { "RELEASE" }
    optimize "On"
  filter {}

  include "script/stem-test/TokenUtilsTest.lua"
  include "script/stem-test/IllegalCharErrorTest.lua"
  include "script/stem-test/NodeTest.lua"
  include "script/stem-test/ReaderTest.lua"
  include "script/stem-test/PLTest.lua"
  include "script/stem-test/LexerTest.lua"
  include "script/stem-test/ParserTest.lua"

workspace "stem-test"