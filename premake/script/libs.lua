-- libs.lua

require "global"

function useTokenLib()
  libdirs {
    (wGLoc .. "/build/stem/token")
  }
  links {
    ("token:shared")
  }
end

function useErrorLib()
  libdirs {
    (wGLoc .. "/build/stem/error")
  }
  links {
    ("error:shared")
  }
end