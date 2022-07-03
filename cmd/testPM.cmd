@echo off

:: remove previous build
del ..\build\PMTest.exe

:: compiling
g++ -I..\interface -I..\inc\util -c ..\src\util\PluginManager.cpp -o ..\bin\pluginManager.o -g
g++ -I..\interface -I..\inc\util -c ..\test\util\PMTest.cpp -o ..\bin\pMTest.o -g

:: building
g++ ..\bin\* -o ..\build\PMTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
cd ..\build
PMTest.exe
cd ..\cmd