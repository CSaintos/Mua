@echo off
:: remove previous build
del ..\build\LexerTest.exe

:: compiling
g++ -I..\inc\util -c ..\src\util\Error.cpp -o ..\bin\error.o -g
g++ -I..\inc\util -c ..\src\util\Token.cpp -o ..\bin\token.o -g
g++ -I..\inc\front -c ..\src\front\Reader.cpp -o ..\bin\reader.o -g
g++ -I..\inc\front -I..\inc\util -c ..\src\front\Lexer.cpp -o ..\bin\lexer.o -g
g++ -I..\inc\front -I..\inc\util -c ..\test\front\LexerTest.cpp -o ..\bin\lexerTest.o -g
:: building
g++ ..\bin\* -o ..\build\LexerTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
..\build\LexerTest.exe ..\script\math.stem