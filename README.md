# &#956;&#965;&#945;

Mua is an open source rudimentary (step-by-step) arithmetic calculator.

## Table of Contents
- [Getting Started](#getting-started)
- [Documentation](#documentation)
- [Building Mua](#building-mua)

## Getting Started
- *repl demo*
- To download Mua, go to [Releases](https://github.com/CSaintos/STEM/releases)
- Install/Place Mua anywhere you'd like on your machine, and to make it easily accessible, add it to your system's or shell's environment path.
## Documentation
- Addition:
`mua>1 + 1;`
`2;`
- Subtraction:
`mua>1-1;`
`0;`
- Multiplication:
`mua>1*1;`
`1;`
- Division:
`mua>-1/(-1);`
`1;`
- Modulation:
`mua>3%4;`
`1;`
- Exponentiation:
`mua>2^3;`
`8;`
- Radical:
`mua>4^(1/2);`
`2;`
## Building Mua
### Requirements
- You will need GCC v11+ or Clang v12+.
- You will need GNU-make 4.4.1+
- If you are on Windows, you can download these packages through [MSYS2](https://www.msys2.org/)
- Make sure to add the installed packages to your system/shell environment path
### Clone, Build, Execute
- clone this repo `git clone https://github.com/CSaintos/STEM.git`
- cd into mua then run `make -j`
- Once completed, the executable is stored in `mua/build/mua/main/muac.exe`
