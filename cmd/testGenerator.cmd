@echo off
:: remove previous build
del ..\build\GeneratorTest.exe

:: compile
g++ -I..\inc\util -c ..\src\util\Error.cpp -o ..\bin\error.o -g
g++ -I..\inc\util -c ..\src\util\Token.cpp -o ..\bin\token.o -g
g++ -I..\inc\util -c ..\src\util\Node.cpp -o ..\bin\node.o -g
g++ -I..\inc\util -I..\interface -c ..\src\util\PluginManager.cpp -o ..\bin\pluginManager.o -g
g++ -I..\inc\front -c ..\src\front\Reader.cpp -o ..\bin\reader.o -g
g++ -I..\inc\front -I..\inc\util -c ..\src\front\Lexer.cpp -o ..\bin\lexer.o -g
g++ -I..\inc\front -I..\inc\util -c ..\src\front\Parser.cpp -o ..\bin\parser.o -g
g++ -I..\inc\back -I..\inc\util -I..\interface -c ..\src\back\Generator.cpp -o ..\bin\generator.o -g
g++ -I..\inc\front -I..\inc\back -I..\inc\util -I..\interface -c ..\test\back\GeneratorTest.cpp -o ^
..\bin\generatorTest.o -g

:: build
g++ ..\bin\* -o ..\build\GeneratorTest.exe
:: clean temp files
del ..\bin\* /F /Q

:: execute build
cd ..\build
GeneratorTest.exe ..\script\math.stem
cd ..\cmd