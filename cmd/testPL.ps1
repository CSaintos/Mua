
Set-Variable -Name "includes" -Value "-Istem\api", "-Istem\inc\util", "-Istem\inc\plugin", "-Istem\inc\util\node\op_node", "-Istem\inc\util\node", "-Istem\inc\util\token"

echo "clean"
rm build\PLTest.exe

echo "compile"
g++ $includes -c stem\src\plugin\PluginLoader.cpp -o bin\PluginLoader.o -g
g++ $includes -c stem\test\plugin\PLTest.cpp -o bin\PLTest.o -g

echo "build"
g++ bin\PluginLoader.o bin\PLTest.o -o build\PLTest.exe

echo "obj-clean"
rm bin\*.o