@echo off

set EXE=Student.exe

if exist bin\%EXE% (
    cd bin
    start %EXE%
) else (
    echo Failed!
)