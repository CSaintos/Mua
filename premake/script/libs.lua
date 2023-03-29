-- libs.lua

require "global"

function useTokenLib()
  libdirs {
    (wGL .. "/build/stem/token")
  }
  links {
    ("token:shared")
  }
end

function useErrorLib()
  libdirs {
    (wGL .. "/build/stem/error")
  }
  links {
    ("error:shared")
  }
end

function useNodeLib()
  libdirs {
    (wGL .. "/build/stem/node")
  }
  links {
    ("node:shared")
  }
end

function useReaderLib()
  libdirs {
    (wGL .. "/build/stem/reader")
  }
  links {
    ("reader:shared")
  }
end

function usePLLib()
  libdirs {
    (wGL .. "/build/stem/PL")
  }
  links {
    ("PL:shared")
  }
end

function useLexerLib()
  libdirs {
    (wGL .. "/build/stem/lexer")
  }
  links {
    ("lexer:shared")
  }
end

function useParserLib()
  libdirs {
    (wGL .. "/build/stem/parser")
  }
  links {
    ("parser:shared")
  }
end

function useGeneratorLib()
  libdirs {
    (wGL .. "/build/stem/generator")
  }
  links {
    ("generator:shared")
  }
end