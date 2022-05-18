@echo off
:: remove previous build
del ..\build\NodeTest.exe

:: compiling
g++ -I..\inc\util -c ..\src\util\Token.cpp -o ..\bin\token.o -g
g++ -I..\inc\util -c ..\src\util\Node.cpp -o ..\bin\node.o -g
g++ -I..\inc\util -c ..\test\util\NodeTest.cpp -o ..\bin\nodeTest.o -g
:: building
g++ ..\bin\token.o ..\bin\node.o ..\bin\nodeTest.o -o ..\build\NodeTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
..\build\NodeTest.exe