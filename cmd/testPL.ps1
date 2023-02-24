
Set-Variable -Name "includes" -Value "-Iapp\api", "-Iapp\inc\util", "-Iapp\inc\util\node\op_node", "-Iapp\inc\util\node", "-Iapp\inc\util\token"

echo "clean"
rm build\PLTest.exe

echo "compile"
g++ $includes -c app\src\util\PluginLoader.cpp -o bin\PluginLoader.o -g
g++ $includes -c app\test\util\PLTest.cpp -o bin\PLTest.o -g

echo "build"
g++ bin\PluginLoader.o bin\PLTest.o -o build\PLTest.exe

echo "obj-clean"
rm bin\*.o