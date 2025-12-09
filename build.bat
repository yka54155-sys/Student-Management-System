@echo off

echo Building.....

set EXE=Student.exe
set CMAKELISTS=..

if not exist build mkdir build 
if not exist bin mkdir bin
cd build
del /q *.*

cmake %CMAKELISTS% -G "MinGW Makefiles"

cmake --build .

cd ..

if exist bin\%EXE% (
    cd bin
    start %EXE%
) else (
    echo Failed!
)
