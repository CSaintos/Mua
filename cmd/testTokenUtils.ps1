
Set-Variable -Name "includes" -Value "-Iinc\util\token", "-Iinc\util"

echo "clean"
rm build\TokenUtilsTest.exe

echo "compile"
g++ $includes -c src\util\token\Token.cpp -o bin\Token.o -g
g++ $includes -c src\util\token\TokenUtils.cpp -o bin\TokenUtils.o -g
g++ $includes -c test\util\token\TokenUtilsTest.cpp -o bin\TokenUtilsTest.o -g

echo "build"
g++ bin\Token.o bin\TokenUtils.o bin\TokenUtilsTest.o -o build\TokenUtilsTest.exe

echo "obj-clean"
rm bin\*.o