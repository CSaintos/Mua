
Set-Variable -Name "includes" -Value "-Istem\inc\front"

echo "clean"
rm build\ReaderTest.exe

echo "compile"
g++ $includes -c stem\src\front\Reader.cpp -o bin\Reader.o -g
g++ $includes -c stem\test\front\ReaderTest.cpp -o bin\ReaderTest.o -g

echo "build"
g++ bin\Reader.o bin\ReaderTest.o -o build\ReaderTest.exe

echo "obj-clean"
rm bin\*.o