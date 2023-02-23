
Set-Variable -Name "includes" -Value "-Iapp\inc\util", "-Iapp\inc\util\token", "-Iapp\inc\util\node", "-Iapp\inc\util\node\value_node", "-Iapp\inc\util\node\op_node"

echo "clean"
rm build\NodeTest.exe

echo "compile"
g++ $includes -c app\src\util\token\TokenUtils.cpp -o bin\TokenUtils.o -g
g++ $includes -c app\src\util\token\Token.cpp -o bin\Token.o -g
g++ $includes -c app\src\util\node\Node.cpp -o bin\Node.o -g
g++ $includes -c app\src\util\node\value_node\DigitNode.cpp -o bin\DigitNode.o -g
g++ $includes -c app\src\util\node\op_node\BinOpNode.cpp -o bin\BinOpNode.o -g
g++ $includes -c app\test\util\node\NodeTest.cpp -o bin\NodeTest.o -g

echo "build"
g++ bin\TokenUtils.o bin\Token.o bin\Node.o bin\DigitNode.o bin\BinOpNode.o bin\NodeTest.o -o build\NodeTest.exe

echo "obj-clean"
rm bin\*.o