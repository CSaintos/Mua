@echo off
:: remove previous build
del ..\build\ReaderTest.exe

:: compiling
g++ -I..\inc\front -c ..\src\front\Reader.cpp -o ..\bin\reader.o -g
g++ -I..\inc\front -c ..\test\front\ReaderTest.cpp -o ..\bin\readerTest.o -g
:: building
g++ ..\bin\reader.o ..\bin\readerTest.o -o ..\build\ReaderTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
..\build\ReaderTest.exe ..\script\math.stem