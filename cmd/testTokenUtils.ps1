
Set-Variable -Name "includes" -Value "-Istem\inc\util\token", "-Istem\inc\util"

echo "clean"
rm build\TokenUtilsTest.exe

echo "compile"
g++ $includes -c stem\src\util\token\Token.cpp -o bin\Token.o -g
g++ $includes -c stem\src\util\token\TokenUtils.cpp -o bin\TokenUtils.o -g
g++ $includes -c stem\test\util\token\TokenUtilsTest.cpp -o bin\TokenUtilsTest.o -g

echo "build"
g++ bin\Token.o bin\TokenUtils.o bin\TokenUtilsTest.o -o build\TokenUtilsTest.exe

echo "obj-clean"
rm bin\*.o