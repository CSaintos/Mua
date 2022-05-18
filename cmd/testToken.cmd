@echo off
:: remove previous build
del ..\build\TokenTest.exe

:: compiling
g++ -I..\inc\util -c ..\src\util\Token.cpp -o ..\bin\token.o -g
g++ -I..\inc\util -c ..\test\util\TokenTest.cpp -o ..\bin\tokenTest.o -g
:: building
g++ ..\bin\token.o ..\bin\tokenTest.o -o ..\build\TokenTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
..\build\TokenTest.exe