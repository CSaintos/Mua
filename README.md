<h1 style="font-size:60px; color:salmon;"> &#956;&#965;&#945; </h1>

Mua is a <span style="color:gray;">(step-by-step, cli-based, arithmetic)</span> calculator.  
Try it out here: https://csaintos.github.io/Mua/#/

![repl demo](./.devcontainer/repl_demo.gif)

## Getting Started
- You may [download Mua](https://github.com/CSaintos/Mua/releases) or begin trying it at https://csaintos.github.io/Mua/#/  
- After downloading, extract the Mua 7z
  - MacOS only: Since MacOS has Gatekeeper, and my app hasn't been notarized by Apple yet. Upon extracting, the file permissions will be set to read-only. You'll want to do a quick `chmod 755 *` inside the mua-macos directory to enable permissions.  
- Install/Place Mua anywhere you'd like on your machine, and to make it easily accessible, add it to your system's or shell's environment path.

## Documentation
- https://csaintos.github.io/Mua/#/doc

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
