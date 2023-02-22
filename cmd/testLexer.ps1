
Set-Variable -Name "includes" -Value "-Iinc\util\error", "-Iinc\util\token", "-Iinc\front", "-Iinc\util"

echo "clean"
rm build\LexerTest.exe

echo "compile"
g++ $includes -c src\util\error\Error.cpp -o bin\Error.o -g
g++ $includes -c src\util\error\IllegalCharError.cpp -o bin\IllegalCharError.o -g
g++ $includes -c src\util\token\TokenUtils.cpp -o bin\TokenUtils.o -g
g++ $includes -c src\util\token\Token.cpp -o bin\Token.o -g
g++ $includes -c src\front\Reader.cpp -o bin\Reader.o -g
g++ $includes -c src\front\Lexer.cpp -o bin\Lexer.o -g
g++ $includes -c test\front\LexerTest.cpp -o bin\LexerTest.o -g

echo "build"
g++ bin\* -o build\LexerTest.exe

echo "obj-clean"
rm bin\*.o