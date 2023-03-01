
Set-Variable -Name "includes" -Value "-Istem\inc\util\error", "-Istem\inc\util\token", "-Istem\inc\front", "-Istem\inc\util"

echo "clean"
rm build\LexerTest.exe

echo "compile"
g++ $includes -c stem\src\util\error\Error.cpp -o bin\Error.o -g
g++ $includes -c stem\src\util\error\IllegalCharError.cpp -o bin\IllegalCharError.o -g
g++ $includes -c stem\src\util\token\TokenUtils.cpp -o bin\TokenUtils.o -g
g++ $includes -c stem\src\util\token\Token.cpp -o bin\Token.o -g
g++ $includes -c stem\src\front\Reader.cpp -o bin\Reader.o -g
g++ $includes -c stem\src\front\Lexer.cpp -o bin\Lexer.o -g
g++ $includes -c stem\test\front\LexerTest.cpp -o bin\LexerTest.o -g

echo "build"
g++ bin\* -o build\LexerTest.exe

echo "obj-clean"
rm bin\*.o