@echo off
:: remove previous build
del ..\build\LexerTest.exe

:: compiling
g++ -I..\inc\util -c ..\src\util\Error.cpp -o ..\bin\error.o -g
g++ -I..\inc\util -c ..\src\util\Token.cpp -o ..\bin\token.o -g
g++ -I..\inc -c ..\src\Reader.cpp -o ..\bin\reader.o -g
g++ -I..\inc -I..\inc\util -c ..\src\Lexer.cpp -o ..\bin\lexer.o -g
g++ -I..\inc -I..\inc\util -c ..\test\LexerTest.cpp -o ..\bin\lexerTest.o -g
:: building
g++ ..\bin\error.o ..\bin\token.o ..\bin\reader.o ..\bin\lexer.o ..\bin\lexerTest.o -o ..\build\LexerTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
..\build\LexerTest.exe ..\script\math.stem