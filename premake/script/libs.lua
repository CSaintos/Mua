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

function useNodeLib()
  libdirs {
    (wGLoc .. "/build/stem/node")
  }
  links {
    ("node:shared")
  }
end

function useReaderLib()
  libdirs {
    (wGLoc .. "/build/stem/reader")
  }
  links {
    ("reader:shared")
  }
end