
Set-Variable -Name "includes" -Value "-Iinterface", "-Iinc\util", "-Iinc\util\node\op_node", "-Iinc\util\node", "-Iinc\util\token"

echo "clean"
rm build\PLTest.exe

echo "compile"
g++ $includes -c src\util\PluginLoader.cpp -o bin\PluginLoader.o -g
g++ $includes -c test\util\PLTest.cpp -o bin\PLTest.o -g

echo "build"
g++ bin\PluginLoader.o bin\PLTest.o -o build\PLTest.exe

echo "obj-clean"
rm bin\*.o