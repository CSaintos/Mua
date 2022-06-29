@echo off

:: remove previous build
del ..\build\PMTest.exe

:: compiling
g++ -I..\inc -c ..\src\PluginManager.cpp -o ..\bin\pluginManager.o -g
g++ -I..\inc -c ..\test\PMTest.cpp -o ..\bin\pMTest.o -g

:: building
g++ ..\bin\* -o ..\build\PMTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
cd ..\build
PMTest.exe
cd ..\cmd