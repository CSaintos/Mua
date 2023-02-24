
Set-Variable -Name "includes" -Value "-Iapp\inc\util", "-Iapp\api", "-Iapp\inc\util\token", "-Iapp\inc\util\node", "-Iapp\inc\util\node\op_node", "-Iplugin\Algebra\inc"

echo "clean"
rm build\plugin\Plus.dll

echo "compile"
g++ -fPIC $includes -c plugin\Algebra\src\Plus.cpp -o bin\Plus.o -g
g++ -fPIC $includes -c app\src\util\token\Token.cpp -o bin\Token.o -g
g++ -fPIC $includes -c app\src\util\token\TokenUtils.cpp -o bin\TokenUtils.o -g

echo "build"
g++ -shared -o build\plugin\Plus.dll bin\*.o -g

echo "obj-clean"
rm bin\*.o