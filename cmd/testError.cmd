@echo off
:: remove previous build
del ..\build\ErrorTest.exe

:: compiling
g++ -I..\inc\util -c ..\src\util\Error.cpp -o ..\bin\error.o -g
g++ -I..\inc\util -c ..\test\util\ErrorTest.cpp -o ..\bin\errorTest.o -g
:: building
g++ ..\bin\error.o ..\bin\errorTest.o -o ..\build\ErrorTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
..\build\ErrorTest.exe