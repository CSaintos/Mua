
Set-Variable -Name "includes" -Value "-Iapp\inc\util\token", "-Iapp\inc\util"

echo "clean"
rm build\TokenUtilsTest.exe

echo "compile"
g++ $includes -c app\src\util\token\Token.cpp -o bin\Token.o -g
g++ $includes -c app\src\util\token\TokenUtils.cpp -o bin\TokenUtils.o -g
g++ $includes -c app\test\util\token\TokenUtilsTest.cpp -o bin\TokenUtilsTest.o -g

echo "build"
g++ bin\Token.o bin\TokenUtils.o bin\TokenUtilsTest.o -o build\TokenUtilsTest.exe

echo "obj-clean"
rm bin\*.o