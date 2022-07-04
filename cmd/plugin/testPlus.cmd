@echo off

:: remove previous build
del ..\..\build\plugin\Plus.dll /F /Q

:: compile
g++ -fPIC -I ..\..\interface ^
-I..\..\plugin\Algebra\inc ^
-I..\..\inc\util -c ^
..\..\plugin\Algebra\src\Plus.cpp ^
-o ..\..\bin\plus.o -g
g++ -fPIC -c ^
..\..\src\util\Token.cpp ^
-I..\..\inc\util ^
-o ..\..\bin\token.o -g

:: build
g++ -shared -o ..\..\build\plugin\Plus.dll ^
..\..\bin\plus.o ^
..\..\bin\token.o -g

:: clean temp files
del ..\..\bin\* /F /Q