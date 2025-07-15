<h1 style="font-size:60px"> &#956;&#965;&#945; </h1>

Mua is a <span style="color:gray">(step-by-step, cli-based, arithmetic)</span> calculator.

![repl demo](./.devcontainer/repl_demo.gif)

## Table of Contents
- [Getting Started](#getting-started)
- [Documentation](#documentation)
- [Building Mua](#building-mua)

## Getting Started
- To download Mua, go to [Releases](https://github.com/CSaintos/Mua/releases)
- Extract the Mua 7z
  - MacOS only: Since MacOS has Gatekeeper, and my app hasn't been notarized by Apple yet. Upon extracting, the file permissions will be set to read-only. You'll want to do a quick `chmod 755 *` inside the mua-macos directory to enable permissions.  
- Install/Place Mua anywhere you'd like on your machine, and to make it easily accessible, add it to your system's or shell's environment path.

## Running Mua
- In your shell: `./muac -h` for how to run mua
### Mua's two modes
##### Repl mode
- Start repl mode with:
`./muac`
- Exit repl mode: `exit[];` on an empty line.
##### File mode
- Evaluate mua file: `./muac <path-to-file>.mua [-o <output-file-path>.muar]`
  - Brackets mean optional argument
- Ex:
  - `./muac ./hello_world.mua`
  - `./muac ./hello_world.mua -o ./hello_world.muar`

## Documentation
### Arithmetic Operators
| Operation | Example | Result |
| --- | --- | --- |
| Addition | `1 + 1;` | `2;` |
| Subtraction | `1-1;` | `0;` |
| Multiplication | `1 * 1;` | `1;` |
| Division | `-1/(-1);` | `1;` |
| Modulation | `4%3;` | `1;` |
| Exponentiation | `2^3;` | `8;` |
| Radication | `4^(1/2);` | `2;` |
| Parentheses | `5-(8-3)` | `0;` |
### Misc
- Comments:
`// A line comment`

## Building Mua
### Requirements
- You will need GCC v11+ or Clang v17+.
  - At a minimum must support c++20
- You will need GNU-make 4.4.1+
- If you are on Windows, you can download these packages through [MSYS2](https://www.msys2.org/)
- Make sure to add the installed packages to your system/shell environment path
### Clone
- clone this repo into an empty directory `git clone https://github.com/CSaintos/Mua.git`
### Build
- Within that same directory, run `make -j`
#### Executable
- Once completed, the executable is stored in `./build/mua/main/muac`
