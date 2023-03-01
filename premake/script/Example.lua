--! Change me
-- Example.lua
project "Example"
  kind "ConsoleApp"
  language "C++"
  location "%{wks.location}/%{prj.name}"

  files {
    "%{wks.location}/../app/src/**.cpp"
  }

  includedirs {
    "%{wks.location}/../app/inc",
    "%{wks.location}/../app/inc/**"
  }

  useExample()