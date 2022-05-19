@echo off
:: remove previous build
del ..\build\ParserTest.exe

:: compiling
g++ -I..\inc\util -c ..\src\util\Error.cpp -o ..\bin\error.o -g
g++ -I..\inc\util -c ..\src\util\Token.cpp -o ..\bin\token.o -g
g++ -I..\inc\util -c ..\src\util\Node.cpp -o ..\bin\node.o -g
g++ -I..\inc -c ..\src\Reader.cpp -o ..\bin\reader.o -g
g++ -I..\inc -I..\inc\util -c ..\src\Lexer.cpp -o ..\bin\lexer.o -g
g++ -I..\inc -I..\inc\util -c ..\src\Parser.cpp -o ..\bin\parser.o -g
g++ -I..\inc -I..\inc\util -c ..\test\ParserTest.cpp -o ^
..\bin\parserTest.o -g
:: building
g++ ..\bin\* -o ..\build\ParserTest.exe
:: cleaning temp files
del ..\bin\* /F /Q

:: execute build
..\build\ParserTest.exe ..\script\math.stem