@echo off
if not exist build mkdir build
if not exist bin mkdir bin

set EXE=SQLitelib.exe

cd build
del /q *.*
cd ..
@REM cd bin
@REM del /q *.*
@REM cd ..

cd build
cmake .. -G "MinGW Makefiles"
mingw32-make

@REM if exist ../bin/%EXE% (
@REM     cd ../bin
@REM     start %EXE%
@REM )