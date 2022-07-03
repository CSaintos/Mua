@echo off

:: remove previous build
del ..\..\build\plugin\Plus.dll /F /Q

:: compile
g++ -fPIC -I ..\..\interface ^
-I..\..\plugin\Algebra\inc -c ^
..\..\plugin\Algebra\src\Plus.cpp ^
-o ..\..\bin\plus.o -g

:: build
g++ -shared -o ..\..\build\plugin\Plus.dll ^
..\..\bin\plus.o -g

:: clean temp files
del ..\..\bin\* /F /Q