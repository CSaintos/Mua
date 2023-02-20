
Set-Variable -Name "includes" -Value "-Iinc\util\error", "-Iinc\util"

echo "clean"
rm build\IllegalCharErrorTest.exe

echo "compile"
g++ $includes -c src\util\error\IllegalCharError.cpp -o bin\IllegalCharError.o -g
g++ $includes -c src\util\error\Error.cpp -o bin\Error.o -g
g++ $includes -c test\util\error\IllegalCharErrorTest.cpp -o bin\IllegalCharErrorTest.o -g

echo "build"
g++ bin\Error.o bin\IllegalCharError.o bin\IllegalCharErrorTest.o -o build\IllegalCharErrorTest.exe

echo "obj-clean"
rm bin\*.o