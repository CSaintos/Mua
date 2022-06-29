@echo off

:: remove previous build
del ..\..\..\build\plugin\Algebra.dll /F /Q

:: compile 
g++ -fPIC -I..\..\..\interface ^
-I..\inc -c ..\src\Algebra.cpp ^
-o ..\..\..\bin\algebra.o -g

:: build
g++ -shared -o ..\..\..\build\plugin\Algebra.dll ^
..\..\..\bin\algebra.o -g

:: clean temp files
del ..\..\..\bin\* /F /Q